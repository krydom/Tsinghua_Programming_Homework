import cv2
import os

image_folder = './results'  # directory to the pictures
video_name = 'output.mp4'  # name for the video


images = [img for img in os.listdir(image_folder) if img.endswith(".png")]
images = sorted(images)
frame = cv2.imread(os.path.join(image_folder, images[0]))
height, width, layers = frame.shape

video = cv2.VideoWriter(video_name, 0x7634706d, 15, (width,height))

for image in images:
    video.write(cv2.imread(os.path.join(image_folder, image)))

cv2.destroyAllWindows()
video.release()