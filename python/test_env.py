import gymnasium as gym
import numpy as np

from Monopoly_Env.env import MonopolyEnv
from Monopoly_Env import Tiles_loader

def start_runs():
    env = MonopolyEnv()
    obs = env.reset()
    done = False

    while not done:
        action = env.action_space.sample()
        obs, reward, done, _ = env.step(action)
        print(f"Position: {np.argmax(obs)}, Cash: {reward}, Done: {done}")

def start_loader():
    tiles_loader = Tiles_loader.Tiles_loader()
    tiles_loader.load()

if __name__ == "__main__":
    start_loader()
    start_runs()
