!!!! Under construction !!!!


Define the host system directory to mount and the container working directory
```
MOUNT_DIR=$PWD:/usr/src/myapp
WORKING_DIR=/usr/src/myapp
```

Get and run the gcc v7 gcc image
```
docker images
docker pull gcc:7
docker images
docker run -it  -v $MOUNT_DIR -w $WORKING_DIR  gcc:7 /bin/bash
gcc -v
```

Build a docker image from Dockerfiles/cpputest3_8.gcc7 and run a bash shell in it
```
docker build -t jamesgrenning/cpputest3_8.gcc7 -f Dockerfiles/cpputest3_8.gcc7 .
docker run -it  -v $MOUNT_DIR -w $WORKING_DIR jamesgrenning/cpputest3_8.gcc7 /bin/bash
make
```

Now you are all set to edit in the native environment and run tests in the Docker container.

