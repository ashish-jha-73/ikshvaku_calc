# 🧮 Ikshvaku Scientific Calculator

A lightweight and powerful scientific calculator built in C++.

> 🪙 Version: 1.0.0  
> 🛠 Platform: Linux (Ubuntu-based systems)

---

## 📸 Preview

This is a terminal-based calculator that:
- Accepts infix expressions like `3 + sin(0.5) * 2`
- Converts to postfix
- Computes the final result
- Supports functions like `sin`, `cos`, `tan`, `log`, `sqrt`, etc.

---

## 🚀 Installation

* **Option 1: Download & Install `.deb` Manually**
  1. Download the latest `.deb` file from the [Releases](https://github.com/ashish-jha-73/ikshvaku_calc/releases) section.
  2. Install it using `dpkg`:
     ```bash
     sudo dpkg -i ikshvaku-calc_1.0_amd64.deb
     sudo apt -f install  # Fix dependencies, if needed
     ```

* **Option 2: Install via Launchpad PPA (Recommended)**
  1. Add the PPA:
     ```bash
     sudo add-apt-repository ppa:ashish-jha-73/calculator
     sudo apt update
     ```
  2. Install the calculator:
     ```bash
     sudo apt install ikshvaku-calc
     ```
