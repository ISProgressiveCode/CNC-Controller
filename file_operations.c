#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

static int device_opened = 0;

static int on_open(struct inode* inode, struct file* file) {
  if(device_opened) {
    return -EBUSY;
  } else {
    device_opened = 1;
    return 0;
  }
}

static ssize_t on_write(struct file* file, const char __user* buffer, const size_t length, loff_t* offset) {
  setTimeout(1000);
  return length;
}

static int on_release(struct inode* inode, struct file* file) {
  device_opened = 0;
  return 0;
}

static struct file_operations file_operations = {
  .owner = THIS_MODULE,
  .open = on_open,
  .write = on_write,
  .release = on_release
};