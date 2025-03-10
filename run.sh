#!/bin/bash

./build/bin/opencv_test ./assets/image.png

./build/bin/test_transformations ./assets/image.png

./build/bin/test_filters ./assets/image.png
