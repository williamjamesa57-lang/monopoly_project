import gymnasium as gym
import numpy as np

from monopoly_cpp import create_game

class MonopolyEnv(gym.Env):
    def __init__(self):
        super().__init__()
        self.game = create_game()
        self.action_space = gym.spaces.Discrete(2)  # Simplified: 0=roll, 1=buy
        self.observation_space = gym.spaces.Box(
            low=0, high=1, shape=(40,), dtype=np.float32
        )

    def step(self, action):
        if action == 0:  
            self.game.roll_dice()
        
        reward = 0
        position = self.game.get_current_player_position()
        tile_state = self.game.get_tile_details()

        if not tile_state.type == tile_state.type.PROPERTY:
            if tile_state.type == tile_state.type.CORNER:
                if tile_state.name == "Jail":
                    reward = -50
                elif tile_state.name == "GO":
                    reward = 200
            elif tile_state.type == tile_state.type.TAX:
                if tile_state.name == "Income Tax":
                    reward = -200
                elif tile_state.name == "Luxury Tax":
                    reward = - 100
            elif tile_state.type == tile_state.type.CARD:
                pass
        else:
            current_action = self.action_space.sample()
            if current_action == 1:
                print(f"Pre pruchase: {tile_state.owner}")
                tile_state = self.game.purchase_tile()
                reward = -1 * tile_state.purchase_price
                print(f"Post pruchase: {tile_state.owner}")
            else:
                reward = 0

        self.game.update_cash(reward)
        done = False

        if self.game.get_cash() < 1:
            done = True #Bankruptcy ends episode
        
        return np.array(self.game.get_state(), dtype=np.float32), self.game.get_cash(), done, {}

    def reset(self):
        self.game = create_game()
        return np.array(self.game.get_state(), dtype=np.float32)