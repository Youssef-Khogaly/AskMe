# AskMe

## Overview
AskMe is a file-based question-and-answer system that allows users to interact by asking and answering questions.
enabling persistent data storage for users, questions, and answers.


## Language: C++ 17

## Features

### Persistent Data Storage
- The system retains data between sessions, storing information about users, questions, and answers.

### Multi-User Support
- Multiple users can use the system concurrently.
- Users can see questions asked by others, answer them, and observe updates in real-time.

### Authentication System
- **Sign Up:** Users can create an account by providing their name, email, password, and username.
- **Login:** Existing users can log in using their credentials.
- **Sign Out:** Users can securely log out of the system.
- **Anonymous Questions:** Users can choose to allow or disallow anonymous questions.

### User Operations
- **View Questions:**
  - Questions asked by the user.
  - Questions directed to the user.
  - General feed of all questions.
- **Ask and Answer Questions:**
  - Users can ask new questions or respond to existing ones.
  - Support for threaded conversations.
- **Delete Questions:**
  - Users can delete their own questions or threads.

### Threaded Question Support
- Questions can form parent threads.
- If a question is answered, follow-up questions can be asked within the original question thread.
- If the parent question is removed, the entire thread is also deleted.

### Data Integrity and Security
- Operations are designed to maintain correctness.
- Users can only see, edit, or delete their own questions and responses.
- Unauthorized actions (e.g., deleting someone else’s question) are prevented.


