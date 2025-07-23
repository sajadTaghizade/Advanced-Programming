<div align="center">
  <h1>
    🚗 Advanced Programming - Computer Assignment 4 🧼
  </h1>
  <h2>
    Object-Oriented Design: Car Wash Management System
  </h2>
  <p>
    This project is the fourth assignment for the Advanced Programming course. The primary goal is to apply <strong>Object-Oriented Design (OOD)</strong> principles to build a comprehensive, event-driven car wash management simulator in C++.
  </p>
</div>

<hr>

<table>
  <tr>
    <td valign="top" width="50%">
      <h3>
        📖 Project Description
      </h3>
      <p>
        The program simulates the operations of a car wash. It manages the flow of cars through various washing stages, assigns workers to tasks, and handles queues when workers are busy. The system operates on a discrete, linear timeline, processing events and user commands to update the state of the entire car wash.
      </p>
      <br>
      <h3>
        ⚙️ Core System Components
      </h3>
      <ul>
        <li>
          <strong>Time</strong>: A linear time model that advances unit by unit, triggering events as they occur.
        </li>
        <li>
          <strong>Workers</strong>: Each assigned to a specific stage with a defined time-to-finish for tasks. The system includes a priority-based assignment logic.
        </li>
        <li>
          <strong>Stages</strong>: Different washing stations with unique prices. Each stage has a queue for waiting cars if all its workers are occupied.
        </li>
        <li>
          <strong>Cars</strong>: Customers who arrive at the car wash with a custom sequence of stages they need to visit.
        </li>
      </ul>
    </td>
    <td valign="top" width="50%">
      <h3>
        🖥️ Simulation Commands
      </h3>
      <p>
        The simulation is controlled through a series of commands entered via standard input:
      </p>
      <details>
        <summary>
          <strong>View Command List</strong>
        </summary>
        <ul>
          <li>
            <strong><code>pass_time &lt;units&gt;</code></strong>: Advances the simulation time and reports all events (e.g., a car finishing a stage, moving to a new stage, or entering a queue) that occurred during that period.
          </li>
          <li>
            <strong><code>car_arrival &lt;stageIDs...&gt;</code></strong>: Adds a new car to the system at the current time with a specified sequence of stages to visit.
          </li>
          <li>
            <strong><code>get_stage_status &lt;stageID&gt;</code></strong>: Displays statistics for a specific stage, including the number of washed cars, cars in the queue, cars currently being washed, and total income.
          </li>
          <li>
            <strong><code>get_worker_status &lt;workerID&gt;</code></strong>: Reports if a worker is currently <code>Idle</code> or <code>Working</code> on a specific car.
          </li>
          <li>
            <strong><code>get_car_status &lt;carID&gt;</code></strong>: Shows the current status of a car (<code>In line</code>, <code>In service</code>, or <code>Done</code>).
          </li>
        </ul>
      </details>
    </td>
  </tr>
</table>

<hr>

### 🛠️ Technical Specifications & Design Goals
The project must be implemented in **C++20** and structured as a **multi-file project** using a `makefile`. The core focus is on proper OOD, which includes:
-   Breaking the problem down into appropriate classes.
-   Separating application logic from input/output.
-   Correct use of access specifiers (`public`/`private`).
-   Keeping the `main` function clean and delegating tasks to objects.

<hr>
