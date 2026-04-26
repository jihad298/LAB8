
# 🧵 LabThreadsAsyncTask — Android Concurrency Lab

## Overview

This Android application demonstrates **multithreading and background processing** in Java using:

* Raw `Thread`
* `Handler`
* `AsyncTask` (educational legacy API)

The goal is to understand how to keep the **UI thread responsive** while executing heavy operations in the background.

---

## Features

* Background image loading using `Thread`
* UI-safe updates using `Handler`
* Heavy computation simulation using `AsyncTask`
* Real-time progress bar updates
* Non-blocking Toast interaction
* UI responsiveness demonstration

---

## Tech Stack

* Java
* Android SDK
* Minimum SDK: 24
* UI: XML (LinearLayout)
* Concurrency: Thread, Handler, AsyncTask

---

## UI Components

* `TextView` → displays status messages
* `ProgressBar` → shows task progress
* `ImageView` → displays loaded image
* Buttons:

  * Load image (Thread)
  * Heavy computation (AsyncTask)
  * Toast test (UI responsiveness)

---

## Architecture Concept

### 1. Thread (Manual background execution)

Used for:

* Image loading simulation
* Avoid blocking UI thread

Key rule:

> UI cannot be updated directly from background threads

Solution:

```java
Handler.post(...)
```

---

### 2. Handler

Bridges background thread → UI thread.

Used to:

* Update ImageView
* Update TextView
* Hide ProgressBar

---

### 3. AsyncTask (educational purpose)

Structured background task:

| Method             | Role              |
| ------------------ | ----------------- |
| onPreExecute()     | UI preparation    |
| doInBackground()   | Heavy computation |
| onProgressUpdate() | Progress updates  |
| onPostExecute()    | Final UI update   |

---

## Application Flow

### Thread Button

1. Start background thread
2. Simulate delay
3. Load bitmap
4. Post result to UI thread
5. Update image + status

---

### AsyncTask Button

1. Show ProgressBar
2. Execute heavy loop computation
3. Update progress (0 → 100)
4. Display final result

---

### Toast Button

* Executes instantly on UI thread
* Confirms UI responsiveness

---

## Key Concepts Demonstrated

* Main thread (UI thread) vs Worker thread
* Thread creation and lifecycle
* UI thread constraints in Android
* Handler communication mechanism
* AsyncTask execution pipeline
* Non-blocking UI design

---

## Expected Behavior

* Toast appears instantly even during background work
* Progress bar updates during computation
* Image loads without freezing UI
* No ANR (Application Not Responding)

---

## Educational Goal

This lab is designed to teach:

* Why Android requires background threads
* How to safely update UI from background tasks
* Differences between Thread and AsyncTask
* Basic concurrency control in Android applications

---
