URL = https://www.youtube.com/watch?v=dQw4w9WgXcQ
DOWNLOAD_PATH = video.mp4
OUTPUT_DIR = video
NAME = video
FPS = 24

all: download extract generate compile

# Run the program
run:
	./a.out

# Compile the C program that load the ascii file
compile:
	gcc -Wall -Wextra -Werror -O3 main.c video.c

# Convert the frames to ascii
generate:
	deno run --allow-all convert.js -- $(OUTPUT_DIR) $(NAME) $(FPS)

# Convert the video in frames
extract:
	rm -rf $(OUTPUT_DIR)
	mkdir -p $(OUTPUT_DIR)
	ffmpeg -i $(DOWNLOAD_PATH) -vf fps=$(FPS) -vframes 256 '${OUTPUT_DIR}/%08d.png'

# Download the youtube video in the lowest quality
download:
	rm -rf $(DOWNLOAD_PATH)
	youtube-dl $(URL) -f worst -o $(DOWNLOAD_PATH)

.PHONY: all run compile generate extract download

