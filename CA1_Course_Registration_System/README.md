<div align="center">
  <h1>
    🎓 Advanced Programming - Computer Assignment 1 💻
  </h1>
  <h2>
    Simplified Course Registration System
  </h2>
  <p>
    This project is the first assignment for the Advanced Programming course, designed as an introduction to using <strong>C++ strings and vectors</strong>. The core task is to implement a simplified university course registration validator, with a strong emphasis on <strong>clean code</strong> and the separation of responsibilities into small, single-purpose functions.
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
        The program simulates a simple course registration system. It receives a list of offered courses for the upcoming semester, a history of the student's previously taken courses with grades, and a list of courses the student wishes to enroll in. The program must then validate this selection against a set of predefined rules.
      </p>
      <br>
      <h3>
        🛠️ Technical Specifications
      </h3>
      <ul>
        <li>
          <strong>Language:</strong> C++20
        </li>
        <li>
          <strong>Compiler:</strong> g++ on a Linux environment
        </li>
        <li>
          <strong>Core Data Structures:</strong> <code>std::vector</code> and <code>std::string</code>
        </li>
      </ul>
    </td>
    <td valign="top" width="50%">
      <h3>
        ✅ Validation Rules
      </h3>
      <p>
        A student's course selection is valid only if it meets all of the following criteria:
      </p>
      <ul>
        <li>
          <strong>Course Offered</strong>: All selected courses must be in the list of offered courses for the semester.
        </li>
        <li>
          <strong>Minimum Units</strong>: The total number of units must be at least 12.
        </li>
        <li>
          <strong>Maximum Units</strong>: The unit limit is based on the student's GPA:
          <ul>
            <li>GPA ≥ 17: <strong>24 units</strong></li>
            <li>12 ≤ GPA < 17: <strong>20 units</strong></li>
            <li>GPA < 12: <strong>14 units</strong></li>
          </ul>
        </li>
        <li>
          <strong>Course Already Taken</strong>: A student cannot re-enroll in a course they have already passed (grade ≥ 10).
        </li>
        <li>
          <strong>Prerequisites Met</strong>: All prerequisites for each selected course must have been passed (grade ≥ 10).
        </li>
      </ul>
    </td>
  </tr>
</table>

<hr>

### 📥 Input and Output Format

<h4>Input</h4>
<p>The program receives data from standard input in three parts: a list of offered courses, a list of taken courses, and the student's desired courses for the new semester.</p>

<h4>Output</h4>
<p>The program outputs <code>OK!</code> if the registration is valid. Otherwise, it prints the first error encountered. The possible error messages are:</p>
<ul>
    <li><code>Course Not Offered!</code></li>
    <li><code>Minimum Units Validation Failed!</code></li>
    <li><code>Maximum Units Validation Failed!</code></li>
    <li><code>Course Already Taken!</code></li>
    <li><code>Prerequisites Not Met!</code></li>
</ul>

<hr>

