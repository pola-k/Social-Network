# Social Network

This project is a simple **Social Network** application implemented in **C++**, created as part of the **Object-Oriented Programming (OOP) course** at university. It allows users to create accounts, manage friendships, and simulate interactions within the network. The project demonstrates fundamental C++ concepts such as classes, oop, and file handling.

## Features

- **User Account Management**: Create new user accounts with a unique username.
- **Friendship Management**: Add and remove friends from a user's friend list.
- **User Details**: Display user information and their list of friends.
- **File Handling**: Save and load user data from a file to preserve state across sessions.

## Getting Started

To run this project locally, you need to have a C++ compiler installed on your system. Follow the instructions below:

### Prerequisites

- **C++ Compiler**: Make sure you have a C++ compiler like `g++` installed. If not, install one using:
    - For Linux/Mac: 
      ```bash
      sudo apt-get install g++
      ```
    - For Windows: Download and install [MinGW](https://www.mingw-w64.org/).

### Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/polak/Social-Network.git
    cd Social-Network
    ```

2. **Compile the source code**:
    ```bash
    g++ social-network.cpp -o social-network
    ```

3. **Run the compiled program**:
    ```bash
    ./social-network
    ```

## Usage

Since there is no user interaction via the command line, you can modify the program behavior by changing the `run` function inside the `SocialNetwork` class. Update the function to implement the required actions, such as adding users, managing friendships, or displaying network information.

## Project Structure

```bash
.
├── social-network.cpp  # Main C++ source file
├── README.md           # Project documentation
└── data.txt            # File used for saving and loading user data (auto-generated)
```

## Code Overview

The project demonstrates the following key C++ concepts:

- **Classes and Objects**: User accounts and friendships are represented using C++ classes.
- **Vectors and Strings**: To store lists of friends and handle user data.
- **File Handling**: For saving and retrieving user data.
- **Customizable Functionality**: The `run` function can be tailored to simulate different network scenarios.


Enjoy experimenting with your social network!
```
