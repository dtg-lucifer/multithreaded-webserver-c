# 🚀 Multi-threaded TCP Server in C

![C](https://img.shields.io/badge/language-C-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

A high-performance multi-threaded TCP server built in C using POSIX threads and a custom thread pool implementation.  
Designed to handle multiple client connections concurrently with clean and modular architecture.

---

## 🧩 Features

- 🔧 Custom **Thread Pool** for efficient task delegation
- 🌐 Handles **multiple TCP clients concurrently**
- 📦 Clean modular architecture (`src/`, `include/`)
- 📜 Simple HTTP-like response (great for testing)
- 🧪 Test with built-in bash script (`load_test.sh`)
- 🪵 Clean logging with response time tracking

---

## 📁 Project Structure

```

.
├── include/               # Header files
│   ├── connection.h
│   ├── server.h
│   ├── threadpool.h
│   └── include.h
├── src/                   # Source files
│   ├── connection.c
│   ├── server.c
│   ├── main.c
│   └── threadpool.c
├── test/                  # Test scripts
├── build/                 # Build outputs (ignored by .gitignore)
├── CMakeLists.txt         # CMake config
├── Makefile               # Makefile (alternative to CMake)
└── README.md              # You are here 😄

````

---

## 🏁 Getting Started

### 🔨 Build using Make

```bash
make
./server
````

### ⚙️ Or use CMake

```bash
mkdir -p build && cd build
cmake ..
make
./server
```

---

## 🔬 Testing the Server

Use the provided load testing script to hammer the server with multiple requests:

```bash
chmod +x test/load.sh
./test/load.sh
```

Or,

```bash
chmod +x test/concurrency.sh
./test/concurrency.sh
```

> You’ll see output like:

```
Request 1: status 200 - 12ms
Request 2: status 200 - 11ms
...
```

---

## ⚒️ Example Output

```
Server is listening on port 8080
Accepted connection from 127.0.0.1:49830
Received data: GET / HTTP/1.1
```

---

## 🔧 Configuration

Default port is defined in `include/include.h`:

```c
#define PORT 8080
#define BUFFER_SIZE 4096
```

---

## 🤝 Contributing

Pull requests are welcome! Feel free to open an issue or fork the repo and submit a PR.

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙏 Acknowledgements

* POSIX `pthreads`
* `curl` for load testing
* Inspiration from Linux `select()` and `epoll` models (coming soon!)

---

### ✨ Future Work

* [ ] Switch to `epoll` for event-driven model
* [ ] Graceful shutdown and signal handling
* [ ] Persistent client sessions
* [ ] JSON response formatting

