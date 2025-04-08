# OOD Test Harness

This multi-threaded, socket-based test harness is built to dynamically execute and log C++ unit tests from DLLs. Written by Hannah Ashton in collaboration with Aamani Suvarna, Katrina Luu, and David Jorgensen in December 2024 using Visual Studio for Syracuse's CSE 687 Object-Oriented Design course.

![Screenshot 2025-04-08 102722](https://github.com/user-attachments/assets/0d6af96b-4809-4d0b-8d8f-77ab31832bd5)
![Screenshot 2025-04-08 102743](https://github.com/user-attachments/assets/93b7701a-b66e-4e23-9b08-ca0facb0d310)


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
