FROM ubuntu
RUN apt-get update && apt-get install -y g++
COPY index.cpp .
RUN g++ /index.cpp -o index
CMD ./index

