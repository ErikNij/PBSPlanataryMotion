import numpy as np
import matplotlib.pyplot as plt

planets_to_load = ["Sun", "Mercury", "Venus", "Earth", "Moon"]

for planet in planets_to_load:
    data = np.loadtxt(planet + ".txt")
    plt.plot(data[:, 1], data[:, 2])

plt.xlabel("X Coordinate")
plt.ylabel("Y Coordinate")
plt.title("Planet Orbits")
plt.grid(True)
plt.legend(planets_to_load)
plt.show()
