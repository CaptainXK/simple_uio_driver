#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

#define UIO_DEV "/dev/uio0"
#define UIO_ADDR "/sys/class/uio/uio0/maps/map0/addr"
#define UIO_SIZE "/sys/class/uio/uio0/maps/map0/size"

static char uio_addr_buf[18], uio_size_buf[18];
static char buff[]="permission123\0";

int main(void){
    int uio_fd, addr_fd, size_fd;
    int uio_size;
    void *uio_addr, *access_address;

    uio_fd = open(UIO_DEV, O_RDWR);//read and write
    addr_fd = open(UIO_ADDR, O_RDONLY);//read only
    size_fd = open(UIO_SIZE, O_RDONLY);//read only
    if(uio_fd<0 
    || addr_fd<0 
    || size_fd<0 
    ){//any one open error
        fprintf(stderr,"fd open error...\n");
        exit(-1);
    }
    read(addr_fd,uio_addr_buf,sizeof(uio_addr_buf));
    read(size_fd,uio_size_buf,sizeof(uio_size_buf));
    uio_addr = (void*)strtoul(uio_addr_buf,NULL,0);
    uio_size = (int *)strtoul(uio_size_buf,NULL,0);

    access_address = mmap(NULL, uio_size, PROT_READ | PROT_WRITE, MAP_SHARED, uio_fd, 0);
    if(access_address == (void *)-1){
        fprintf(stderr, "mmap error...\n");
        exit(-1);
    }
    printf("The device address %p (length %d)\n"
           "can be accessed over\n"
           "logical address %p\n", uio_addr, uio_size, access_address);
    // int ret = write(uio_fd, buff, strlen(buff));
    char * start = (char *)access_address;
    // strcpy(start,buff);
    for(int i=0; i<1024; i++){
        printf("%c",start[i]);
    }
    printf("\n");
    // if(ret >= 0){
    //     printf("write %d bytes into dev\n",ret);
    // }
    // else{
    //     // fprintf(stderr, "error (%d)...\n",errno);
    //     // printf("%s",strerror(errno));
    //     perror("error:");
    //     exit(-1);
    // }
    
    return 0;
}