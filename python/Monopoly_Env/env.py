import gymnasium as gym
import numpy as np

from monopoly_cpp import create_game
from monopoly_cpp import Tile_type

ACTION_MEANINGS = {
    0 : "roll_dice",
    1 : "purchase_property",
    2 : "build_house",
    3 : "mortgage_property",
    4 : "unmortgage_property",
    5 : "skip_action",    
}   

class MonopolyEnv(gym.Env):
    def __init__(self):
        super().__init__()
        self.game = create_game()
        self.action_space = gym.spaces.Discrete(len(ACTION_MEANINGS))
        self.observation_space = gym.spaces.Dict({
            "position" : gym.spaces.Discrete(40),
            "cash" : gym.spaces.Box(
                low = 0,
                high = 10000,
                shape = (1,),
                dtype = np.float32
            ),
            "properties_owned" : gym.spaces.MultiBinary(28),
            "houses_built" : gym.spaces.Box(
                low = 0,
                high = 5,
                shape = (28, ),
                dtype = np.int32,
            ),
            "mortgaged_properties" : gym.spaces.MultiBinary(28)
        })

    def step(self, action_idx):
        action = ACTION_MEANINGS[action_idx]
        reward = 0.0
        position = self.game.get_current_player_position()
        tile_state = self.game.get_tile_details()


        if action == "roll_dice":
            self.game.roll_dice()
            new_position = self.game.get_current_player_position()
            new_tile_state = self.game.get_tile_details()
            reward += self.landing_protocol(new_tile_state)
            
        elif action == "purchase_property":
            if tile_state.owner == -1 and self._can_afford(tile_state,tile_state.house_price):
                new_tile_copy = tile_state
                new_tile_copy.owner = 0
                self.game.modify_tile_info(new_tile_copy)
                self.game.update_cash(-new_tile_copy.purchase_price)
                reward -= new_tile_copy.purchase_price
                print("purchased")
                #to update make a color monopoly feature
        
        elif action == "build_house":
            if self._can_build_house(tile_state, 0):
                new_tile_copy = tile_state
                new_tile_copy.house_count += 1
                self.game.modify_tile_info(new_tile_copy)
                cost = new_tile_copy.house_price
                self.game.update_cash(-cost)
                reward -= cost
                
                # to do include monopoly development feature
                
        elif action == "mortgage_property":
            if self._can_mortgage(tile_state, 0):
                new_tile_copy = tile_state
                new_tile_copy.is_mortgaged = True
                self.game.modify_tile_info(new_tile_copy)
                cash_received = 0 # to do make the mortgage valuation feature
                self.game.update_cash(cash_received)
                reward += cash_received

                # to do make a strategic property mortgage penalizer
                
        elif action == "unmortgage_property":
            if self._can_unmortgage(tile_state, 0):
                new_tile_copy = tile_state
                new_tile_copy.is_mortgaged = False
                self.game.modify_tile_info(new_tile_copy)
                cost = 0 # to do unmortgage valuations feature
                self.game.update_cash(-cost)

                reward -= cost
                
        elif action == "skip_action":
            reward -= 1

        done = False

        if self.game.get_cash() < 1:
            done = True #Bankruptcy ends episode
        
        return np.array(self.game.get_state(), dtype=np.float32), self.game.get_cash(), done, {}

    def reset(self):
        self.game = create_game()
        return np.array(self.game.get_state(), dtype=np.float32)

    def landing_protocol(self, tile_state):
        reward = 0.0

        if not tile_state.type == tile_state.type.PROPERTY:
            if tile_state.type == tile_state.type.CORNER:
                if tile_state.name == "Jail":
                    reward = -50
                elif tile_state.name == "GO":
                    reward += 200
            elif tile_state.type == tile_state.type.TAX:
                reward -= tile_state.purchase_price
            elif tile_state.type == tile_state.type.CARD:
                pass
        else:
            current_action = self.action_space.sample()
            if current_action == 1:
                tile_state.owner = 0
                reward = -1 * tile_state.purchase_price
            else:
                reward = 0

        return reward

    def _can_afford(self, tile, cost):
        my_tile_info = Tile_type.PROPERTY
        tile_legibility = tile.type == my_tile_info
        can_afford = self.game.get_cash() > cost
        return can_afford and tile_legibility

    def _can_build_house(self, tile, player_number):
        my_tile_info = Tile_type.PROPERTY
        ownership_check = tile.owner == player_number
        affordability_check = self.game.get_cash() > tile.house_price
        tile_legibility = tile.type == my_tile_info
        max_five_house_check = not (tile.house_count >= 5)
        return ownership_check and affordability_check and max_five_house_check and tile_legibility

    def _can_mortgage(self, tile, player_number):
        can_mortgage = tile.is_mortgaged == False
        is_owner = tile.owner == player_number
        return can_mortgage and is_owner

    def _can_unmortgage(self, tile, player_number):
        can_unmortgage = tile.is_mortgaged == True
        is_owner = tile.owner == player_number
        return can_unmortgage and is_owner
