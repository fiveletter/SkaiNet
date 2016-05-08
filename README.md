# **SkyNet: Self-tracking Tripod**
----
SkyNet is a tracking tripod mount that will follow a given target using computer vision techologies. The system utilizes two brushless motors that are controlled by inputs given from a Raspberry Pi 3. The Raspberry Pi 3 utilizes OpenCV open source library to caluclate the deviation of a tracked object from the center of its view. It will then control the motors to correct the camera position such that the target will always be in the center of the video. The mount will be able to hold point-and-shoot cameras or smartphones for video recording.
