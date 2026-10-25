# OpenGL Sphere Physics Engine

A lightweight C++ graphics and physics simulation project featuring a custom **OpenGL rendering engine** coupled with a rigid-body **physics engine** capable of simulating force, acceleration, velocity, torque, and rotational motion on a 3D sphere.

---

## 🚀 Features

* **Custom OpenGL Rendering Engine:** Renders a 3D sphere with real-time lighting and transformations.
* **Rigid-Body Physics Simulation:** Custom physics pipeline handling linear motion (forces, acceleration, velocity) and rotational motion (torque, angular acceleration, angular velocity).
* **Interactive Keyboard Controls:** Real-time application of forces and torques using GLFW.

---

## Upcoming Features:
 * Collision Detection
 * Collision Reaction
 * Rendering of Multiple Bodies
## 🎮 Controls

### Camera / General Navigation
* **`W` / `A` / `S` / `D`**: Generic movement controls.
* **`Hold Down LMB and Move Mouse`**: Generic camera Controls controls.

### Sphere Force Controls (Linear Motion)
* **`E` / `Q`**: Move along the X-axis (`+X` / `-X`)
* **`Z` / `X`**: Move along the Y-axis (`+Y` / `-Y`)
* **`C` / `V`**: Move along the Z-axis (`+Z` / `-Z`)

### Sphere Torque Controls (Rotational Motion)
* **`H` / `J`**: Apply torque around the X-axis
* **`K` / `L`**: Apply torque around the Y-axis
* **`M` / `N`**: Apply torque around the Z-axis

---

## 🛠️ Physics Input Implementation

The physics interaction is driven by real-time GLFW polling for forces and torques:

```cpp
void PhysicsBody::applyForceOnKeyPress(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        applyForce(glm::vec3(0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        applyForce(glm::vec3(-0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, -0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.0, 0.01));
    }
    else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        applyForce(glm::vec3(0.0, 0.0, -0.01));
    }
    else {
        this->acc = glm::vec3(0.0f);
        this->vel = glm::vec3(0.0f);
    }
}

void PhysicsBody::applyTorqueOnKeyPress(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        applyTorque(glm::vec3(0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        applyTorque(glm::vec3(-0.01, 0.0, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        applyTorque(glm::vec3(0.0, 0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        applyTorque(glm::vec3(0.0, -0.01, 0.0));
    }
    else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        applyTorque(glm::vec3(0.0, 0.0, 0.01));
    }
    else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        applyTorque(glm::vec3(0.0, 0.0, -0.01));
    }
    else {
        angVel = glm::vec3(0.0, 0.0, 0.0);
        angAcc = glm::vec3(0.0, 0.0, 0.0);
    }
}
