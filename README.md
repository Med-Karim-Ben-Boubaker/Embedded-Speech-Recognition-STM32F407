# Embedded-Speech-Recognition-STM32F407


![RTOS Implimentation](https://img.shields.io/badge/RTOS_Implimentation-In_Progress-orange)
![RTOS Implimentation](https://img.shields.io/badge/license-MIT-green)
![RTOS Implimentation](https://img.shields.io/badge/Version-v1.0.0-blue)
## Overview

This project will implement a speech command recognition system on an STM32F407 Discovery board with **112KB** of **RAM**. The system is designed to predict two keywords, "yes" and "no," while classifying other sounds as "noise." It utilizes embedded audio processing and deep learning techniques to achieve efficient speech recognition on a microcontroller platform.
## Project Structure

The project is divided into two main parts:
1. **Firmware for STM32F407:**
	- The firmware is responsible for capturing audio input, performing pre-processing (such as filtering and feature extraction), and running the neural network model to predict the keywords or classify noise.
2. **Deep Learning Model**:
	- The deep learning model is developed in a Jupyter Notebook and is trained to recognize the keywords "yes" and "no" and classify "Noise."
	- This part includes the model training, evaluation, and conversion into a format that can be deployed on the STM32 microcontroller.
	- Python code interfaces with the STM32F407 via USB to receive spectrogram data for debugging purposes and record audio samples for training.

## Getting Started

### Installation
1. **Clone the repository**:
```bash
git clone https://github.com/Med-Karim-Ben-Boubaker/Embedded-Speech-Recognition-STM32F407.git
```
2. **Setup the Python environment:**
- if you want to run notebook cells or scripts, you need to install some dependencies
```bash
pip install -r requirements.txt
```
3. **Setup the STM32 environment:**
- You just need to open the project file of stm32 in STM32CubeIDE and flash the code, the model is already integrated with the code, so no need to retrain and redeploy it.

## Documentation and Theory:

The project, proposed by [ACTIA Engineering Services Tunisia](https://www.actia.com/pays/tunisie/) as a two-month internship, aims to integrate AI-based solutions into embedded systems with limited resources and strict memory constraints. Since there is no direct toolchain for deploying and analyzing such models, a pre-processing phase was implemented using various libraries. Detailed documentation and an application note for this project are currently in development, you can check the `docs` folder for more details.

The tutorial will cover techniques for data pre-processing, including creating spectrograms, converting PDM to PCM data using FIR filters, and designing tinyML models for audio classification tasks.

## Future Improvements

This project can serve as a template for audio classification tasks. However, several improvements are necessary to enhance its functionality and user experience:
### Integration Challenges:
- The current code architecture may be difficult to integrate into other real-time systems.
- A new implementation based on an RTOS like FreeRTOS is recommended to improve compatibility and performance.
### Reliability of Real-Time Speech Recognition:
- The system currently processes audio samples discretely every second.
- This approach can lead to unreliability in detecting keywords, as users may speak the keyword between two snapshots, resulting in missed detections.
### Proposed Feature for Enhanced User Experience:
- Implement a feature that waits for the user to initiate speech before starting to capture audio.
- This change would ensure that keywords are detected more reliably, as the system would be actively listening for user input rather than relying on fixed time intervals.
By addressing these areas, the project can significantly improve its usability and effectiveness in real-time audio classification tasks.
