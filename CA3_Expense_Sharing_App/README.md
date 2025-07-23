<div align="center">
  <h1>
    💸 Advanced Programming - Computer Assignment 3 💳
  </h1>
  <h2>
    "UT-Pay": A Simplified Expense Sharing Application
  </h2>
  <p>
    This project is the third assignment for the Advanced Programming course, focusing on <strong>Top-Down Design</strong> and file processing in C++. The core task is to implement a simplified version of an expense-sharing application like Splitwise, which calculates and optimizes debts among a group of people.
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
        The program, named "UT-Pay," processes two input CSV files: one containing a list of users and another detailing various expenses. It calculates each person's final balance (how much they are owed or how much they owe). Finally, it implements an optimization algorithm to simplify the debts into the minimum number of transactions required to settle all balances.
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
          <strong>Input:</strong> User and expense data from CSV files passed as command-line arguments.
        </li>
        <li>
          <strong>Key Challenge:</strong> Designing the program by breaking the problem down into smaller, manageable functions before implementation. Object-Oriented Programming is not permitted for this assignment.
        </li>
      </ul>
    </td>
    <td valign="top" width="50%">
      <h3>
        💸 Expense Types
      </h3>
      <p>
        The application supports three different ways to split expenses:
      </p>
      <ul>
        <li>
          <strong>Equally</strong>: The total cost is split equally among specified borrowers. If no borrowers are listed, the cost is split among everyone in the group.
        </li>
        <li>
          <strong>Unequally</strong>: The exact share for each borrower is specified in the input file.
        </li>
        <li>
          <strong>Adjustment</strong>: Specific users have extra amounts added to their share, and the remaining cost is split equally among everyone.
        </li>
      </ul>
      <h3>
        🔄 Debt Optimization
      </h3>
      <p>
        After calculating the final balance for each person, an optimization algorithm is used to settle the debts. The person who owes the most pays the person who is owed the most, and this process repeats until all debts are cleared, minimizing the total number of transactions.
      </p>
    </td>
  </tr>
</table>

<hr>
