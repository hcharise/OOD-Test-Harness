# OOD Test Harness

This multi-threaded, socket-based test harness is built to dynamically execute and log C++ unit tests from DLLs. Written by Hannah Ashton in collaboration with Aamani Suvarna, Katrina Luu, and David Jorgensen in December 2024 using Visual Studio for Syracuse's CSE 687 Object-Oriented Design course.

![image](https://github.com/user-attachments/assets/29773a8a-a609-4009-825d-36e47163bae8)

## 🧩 Overview

This project implements a general-purpose test harness framework that executes C++ tests defined in external DLLs. Test configurations are serialized into JSONs and passed to the test harness, which deserializes and then dynamically loads the DLLs, runs the tests in parallel threads, and logs the results using socket-based communication.

## 🧱 Architecture
![image](https://github.com/user-attachments/assets/cf5ad8fd-6510-4a42-a108-133316f5e062)

### 🧷 External Components

- **Program to Test**  
  The external application logic, compiled as one or more DLLs.

- **Test Declarations**  
  JSON-formatted files that declare:
  - DLL name
  - Function to test
  - Parameters
  - Expected results

### 🧩 Internal Components

- **TestHarness**
  - Central controller that loads tests, manages communication, executes tests, and logs results.
  - Runs multiple threads: one for socket communication, the rest for executing tests.

- **Executor**
  - Executes test functions from DLLs.
  - Catches exceptions and formats output into result messages.

- **ResultLog**
  - Tracks test metadata: test ID, status, DLL, parameters, timestamp, and error messages.

- **ThreadPool**
  - Manages multiple executor threads for concurrent test execution.

- **Socket Communication**  
  - Handles TCP messaging between the sender of test declarations and the test harness.

## ⚙️ How It Works

![image](https://github.com/user-attachments/assets/0133e2e7-c7a6-4005-aae7-486dff6c5852)

1. **Test declarations** are defined and serialized in JSON format.
2. The **TestHarness**:
   - Deserializes test specs
   - Dynamically loads DLLs
   - Dispatches execution to available threads in the pool
3. Each **Executor**:
   - Executes the specified function
   - Captures result, status, and any errors
   - Creates a **Message** object with result data
4. The **TestHarness**:
   - Deserializes messages
   - Logs output via `ResultLog`
  
## 🚀 Running the Harness

### 1. 📥 Download the Code

  Clone the repository using Git:

```bash
  git clone https://github.com/your-username/OOD-Test-Harness.git
```

  Or download it as a ZIP and extract it.

### 2. 🧑‍💻 Open the Project in Visual Studio
Open Visual Studio 2022 (or newer).
Go to File → Open → Project/Solution.
Select the .sln file in the root directory of the repository.
Restore any NuGet packages if prompted.

### 3. 🧩 Build and Set Up DLLs
The Test Harness dynamically loads test cases defined in DLLs. You need to:
  - Create your own DLLs that implement test functions
  - Export test functions via a common interface (e.g., iTest)
  - Declare test functions in a test declaration JSON file

If you're new to DLLs in C++, follow this [official Microsoft tutorial](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170) to learn how to create and use them.

Once you've created the DLL:
  - Build the DLL project in Visual Studio.
  - Copy the resulting .dll file to the appropriate location specified in your test declaration JSON.
  - Update your test declaration file with:
     - DLL name
     - Function name
     - Parameters (if any)

### 4. ▶️ Run the Harness
Press F5 in Visual Studio or run the compiled executable from the command line.
The harness will:
  - Load the test declarations
  - Load the specified DLLs
  - Run all declared tests in parallel threads
  - Log and display results in the console or output log

📌 Make sure your DLLs are compiled in the same architecture (x64/x86) as the test harness project!
