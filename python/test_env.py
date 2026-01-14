import gymnasium as gym
import numpy as np

from Monopoly_Env.env import MonopolyEnv
env = MonopolyEnv()
obs = env.reset()
done = False

while not done:
    action = env.action_space.sample()
    obs, reward, done, _ = env.step(action)
    print(f"Position: {np.argmax(obs)}, Cash: {reward}, Done: {done}")