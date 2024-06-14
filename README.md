
# 2D Rouge

Welcome to this repository, a 2D Rogue-like game set in a 3D environment. This project was initially created as a learning exercise and, while well-designed, embodies many opportunities for refinement and optimization. 

### Built With

- **Unreal Engine 5.3**
- **GameplayAbilitySystem Framework**
- **Data-Driven Design Approach**

### Features

- **Core Gameplay Abilities**: Utilizes custom ability tasks, gameplay abilities, and dynamic gameplay effects.
- **Experience System**: Implements XP handling and progression.
- **Weapon System**: Features weapon pooling with weapon proxies for efficient management.
- **User Interface**: Complete UI setup with controllers to display essential information like health, XP, and inventory.

### Asynchronous Loading

- The game incorporates asynchronous loading using `TSoftObjectPtr` and manages assets with `AssetManager` using `PrimaryIds` to ensure smooth gameplay experience without load-time disruptions.

### Getting Started

To get started with the development or improvement of **Rogue Venture**, follow these setup instructions:

1. **Clone the repository**:
   ```
   git clone [repository-url]
   ```
2. **Open the project in Unreal Engine**:
   - Navigate to the project folder.
   - Double-click the project file to open it in Unreal Engine 5.3.

3. **Explore the Project**:
   - The `Content` folder contains all the assets and blueprints.
   - Core gameplay systems are located under the `GameplayAbilitySystem` directories.

### Contributing

If you are interested in improving the project, please consider the following:
- While the project is functional, many implementations can be optimized.
- Contributions to refactor or enhance the existing systems are highly welcome.

### License

Distributed under the MIT License. See `LICENSE` file for more information.

### Acknowledgments

- This project was a stepping stone in learning advanced game development techniques and Unreal Engine's robust systems.

### Note

This game was developed as a learning project. The code and systems design, while functional, are not optimized for production use and may embody unconventional or deprecated methods due to the experimental nature of the learning process.

---

This README is structured to provide a concise yet informative overview of your game, highlighting its features, and setup, while also encouraging further development and optimization.
