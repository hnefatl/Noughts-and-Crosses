@echo off
cd E:\Programming\C++\AI\XO\
gource --fullscreen -i 3000 --key --multi-sampling --title XO --bloom-intensity 1.5 -o Video.ppm
ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i Video.ppm -vcodec libx264 -preset ultrafast -pix_fmt yuv420p -crf 1 -threads 0 -bf 0 Video.avi
del Video.ppm