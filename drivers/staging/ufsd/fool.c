#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>

#include <linux/fs.h>
#include <linux/writeback.h>
#include <linux/preempt.h>
#include <linux/lockdep.h>

#include "config.h"
#include "ufsdapi.h"

static void fool(const char * name)
{
	printk("fatal error: fool function %s called\n", name);
	mdelay(1000);
	BUG();
	*(int*)0=0;
}

#define MAKE_FOOL(x) void x(void){fool(#x);}

MAKE_FOOL(block_prepare_write);
MAKE_FOOL(block_sync_page);
MAKE_FOOL(create_proc_entry);
MAKE_FOOL(d_alloc_anon);
MAKE_FOOL(d_alloc_root);
MAKE_FOOL(file_fsync);
MAKE_FOOL(generic_commit_write);
MAKE_FOOL(generic_file_sendfile);
MAKE_FOOL(get_sb_bdev);
MAKE_FOOL(posix_acl_chmod_masq);
MAKE_FOOL(posix_acl_clone);
MAKE_FOOL(posix_acl_create_masq);

MAKE_FOOL(_spin_lock);
MAKE_FOOL(xtime);
MAKE_FOOL(_clear_bit_le);
MAKE_FOOL(__bug);
MAKE_FOOL(_test_and_set_bit_le);
MAKE_FOOL(_set_bit_le);

#if defined(UFSD_BUILT_AS_MODULE)
MAKE_FOOL(posix_acl_from_xattr);
MAKE_FOOL(posix_acl_valid);
MAKE_FOOL(posix_acl_permission);
MAKE_FOOL(posix_acl_equiv_mode);
MAKE_FOOL(posix_acl_to_xattr);
#endif

//MAKE_FOOL(vmtruncate);
//MAKE_FOOL(end_writeback);
//MAKE_FOOL(writeback_inodes_sb_if_idle);
//MAKE_FOOL(__blockdev_direct_IO);

int writeback_inodes_sb_if_idle(struct super_block *sb, enum wb_reason reason)
{
    return try_to_writeback_inodes_sb(sb, reason);
}

int vmtruncate(struct inode *inode, loff_t offset)
{
    return inode_newsize_ok(inode, offset);
}

void end_writeback(struct inode *inode)
{
    clear_inode(inode);
}
