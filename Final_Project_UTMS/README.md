<div align="center">
  <h1>
    🎓 UTMS: University Management & Social System 🎓
  </h1>
  <h2>
    Final Project for Advanced Programming
  </h2>
  <p>
    This repository contains the final capstone project for the Advanced Programming course. The project involves the design and implementation of a comprehensive <strong>University Management System (UTMS)</strong> with integrated social media features. It combines all the core concepts learned throughout the semester, including <strong>Object-Oriented Design</strong>, multi-file projects, and a client-server architecture.
  </p>
</div>

<hr>

<table>
  <tr>
    <td valign="top" width="50%">
      <h3>
        📖 Core System Features
      </h3>
      <ul>
        <li>
          <strong>User Management</strong>: Supports three distinct user roles (Student, Professor, Admin) with a secure login system.
        </li>
        <li>
          <strong>Course Management</strong>: Allows admins to offer courses and students to enroll in or drop them based on prerequisites and schedules.
        </li>
        <li>
          <strong>Social Networking</strong>: Users can create posts (with text and images), view personal pages, and connect with each other.
        </li>
        <li>
          <strong>TA Application System</strong>: Professors can post Teaching Assistant (TA) forms, and students can apply, creating a full application lifecycle.
        </li>
        <li>
          <strong>Notification System</strong>: Automatically sends notifications for key events like new posts, course offerings, and TA application results.
        </li>
      </ul>
    </td>
    <td valign="top" width="50%">
      <h3>
        🛠️ Key Technologies & Concepts
      </h3>
      <ul>
        <li>
          <strong>Language:</strong> C++20
        </li>
        <li>
          <strong>Core Paradigm:</strong> Object-Oriented Design (OOD)
        </li>
        <li>
          <strong>Project Structure:</strong> Multi-file project built with a <code>Makefile</code>.
        </li>
        <li>
          <strong>Data Handling:</strong> Reading initial data from CSV files and managing program state.
        </li>
        <li>
          <strong>Architecture:</strong>
          <ul>
            <li>Phase 1: Command-Line Interface (CLI)</li>
            <li>Phase 2: Client-Server Model (HTTP Web Server)</li>
          </ul>
        </li>
      </ul>
    </td>
  </tr>
</table>

<hr>

## 🚀 Project Phases

<details>
  <summary>
    <h3>Phase 1: Core Logic & Command-Line Interface</h3>
  </summary>
  <p>
    The first phase focused on building the entire backend logic of the UTMS application. All interactions were handled through a custom Command-Line Interface (CLI) that accepted commands with specific methods (<code>GET</code>, <code>POST</code>, <code>PUT</code>, <code>DELETE</code>) and arguments.
  </p>
  <h4>Key Features Implemented:</h4>
  <ul>
    <li>
      <strong>User Authentication</strong>: Secure login/logout for all user types.
    </li>
    <li>
      <strong>Social Platform</strong>: Creating, viewing, and deleting posts; viewing user profiles; and establishing two-way connections between users.
    </li>
    <li>
      <strong>Academic System</strong>: Admins can offer courses, and students can enroll/drop based on complex validation rules (prerequisites, major, schedule conflicts).
    </li>
    <li>
      <strong>TA Recruitment</strong>: Professors can create and close TA application forms, and students can submit their applications.
    </li>
  </ul>
</details>

<details>
  <summary>
    <h3>Phase 2: Web Server & HTML Interface</h3>
  </summary>
  <p>
    In the second phase, the CLI was replaced with a graphical user interface on the web. The backend logic from Phase 1 was exposed through a web server built using a provided C++ HTTP library. The frontend was created using HTML, transforming the application into a functional client-server model.
  </p>
  <h4>Key Features Implemented:</h4>
  <ul>
    <li>
      <strong>Web Server</strong>: Handled GET and POST requests to serve dynamic content.
    </li>
    <li>
      <strong>Session Management</strong>: Used Session IDs to manage logged-in users across different requests.
    </li>
    <li>
      <strong>HTML Interface</strong>: Created web pages for all major functionalities, including a login page, user homepages, forms for creating posts, course enrollment, and TA applications, all with image upload capabilities.
    </li>
    <li>
      <strong>Bonus Features</strong>: The project had optional extensions for using CSS for styling and JavaScript for interactive elements.
    </li>
  </ul>
</details>

<hr>
