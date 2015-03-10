 
#pragma once 
struct block_device; 
typedef struct block_device **block_dev_t; 

typedef uint16_t page_address_t; 

typedef enum {
	BLKDEV_BUSY = (1 << 0)
} blkdev_status_t; 

struct block_device_geometry {
	uint16_t page_size; 
	uint16_t pages; 
	uint16_t sectors; 
}; 

struct block_device {
	uint8_t (*open)(block_dev_t self); 
	int8_t 	(*close)(block_dev_t self); 
	ssize_t (*writepage)(block_dev_t self, page_address_t page, const uint8_t *data, ssize_t data_size); 
	ssize_t (*readpage)(block_dev_t self, page_address_t page, uint8_t *data, ssize_t data_size); 
	int8_t 	(*get_geometry)(block_dev_t self, struct block_device_geometry *geom); 
	uint8_t (*get_status)(block_dev_t self, blkdev_status_t flags); 
}; 

#define blk_open(dev) (*dev)->open(dev)
#define blk_close(dev) (*dev)->close(dev)
#define blk_writepage(dev, page, data, size) (*dev)->writepage(dev, page, data, size)
#define blk_readpage(dev, page, data, size) (*dev)->readpage(dev, page, data, size)
#define blk_get_geometry(dev, geom) (*dev)->get_geometry(dev, geom)
#define blk_get_status(dev, flags) (*dev)->get_status(dev, flags)
