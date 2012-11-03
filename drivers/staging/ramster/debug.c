#include <linux/atomic.h>
#include "debug.h"

#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#define	zdfs	debugfs_create_size_t
#define	zdfs64	debugfs_create_u64
int zcache_debugfs_init(void)
{
	struct dentry *root = debugfs_create_dir("zcache", NULL);
	if (root == NULL)
		return -ENXIO;

	zdfs("obj_count", S_IRUGO, root, &zcache_obj_count);
	zdfs("obj_count_max", S_IRUGO, root, &zcache_obj_count_max);
	zdfs("objnode_count", S_IRUGO, root, &zcache_objnode_count);
	zdfs("objnode_count_max", S_IRUGO, root, &zcache_objnode_count_max);
	zdfs("flush_total", S_IRUGO, root, &zcache_flush_total);
	zdfs("flush_found", S_IRUGO, root, &zcache_flush_found);
	zdfs("flobj_total", S_IRUGO, root, &zcache_flobj_total);
	zdfs("flobj_found", S_IRUGO, root, &zcache_flobj_found);
	zdfs("failed_eph_puts", S_IRUGO, root, &zcache_failed_eph_puts);
	zdfs("failed_pers_puts", S_IRUGO, root, &zcache_failed_pers_puts);
	zdfs("failed_get_free_pages", S_IRUGO, root,
				&zcache_failed_getfreepages);
	zdfs("failed_alloc", S_IRUGO, root, &zcache_failed_alloc);
	zdfs("put_to_flush", S_IRUGO, root, &zcache_put_to_flush);
	zdfs("compress_poor", S_IRUGO, root, &zcache_compress_poor);
	zdfs("mean_compress_poor", S_IRUGO, root, &zcache_mean_compress_poor);
	zdfs("eph_ate_tail", S_IRUGO, root, &zcache_eph_ate_tail);
	zdfs("eph_ate_tail_failed", S_IRUGO, root, &zcache_eph_ate_tail_failed);
	zdfs("pers_ate_eph", S_IRUGO, root, &zcache_pers_ate_eph);
	zdfs("pers_ate_eph_failed", S_IRUGO, root, &zcache_pers_ate_eph_failed);
	zdfs("evicted_eph_zpages", S_IRUGO, root, &zcache_evicted_eph_zpages);
	zdfs("evicted_eph_pageframes", S_IRUGO, root,
				&zcache_evicted_eph_pageframes);
	zdfs("eph_pageframes", S_IRUGO, root, &zcache_eph_pageframes);
	zdfs("eph_pageframes_max", S_IRUGO, root, &zcache_eph_pageframes_max);
	zdfs("pers_pageframes", S_IRUGO, root, &zcache_pers_pageframes);
	zdfs("pers_pageframes_max", S_IRUGO, root, &zcache_pers_pageframes_max);
	zdfs("eph_zpages", S_IRUGO, root, &zcache_eph_zpages);
	zdfs("eph_zpages_max", S_IRUGO, root, &zcache_eph_zpages_max);
	zdfs("pers_zpages", S_IRUGO, root, &zcache_pers_zpages);
	zdfs("pers_zpages_max", S_IRUGO, root, &zcache_pers_zpages_max);
	zdfs("last_active_file_pageframes", S_IRUGO, root,
				&zcache_last_active_file_pageframes);
	zdfs("last_inactive_file_pageframes", S_IRUGO, root,
				&zcache_last_inactive_file_pageframes);
	zdfs("last_active_anon_pageframes", S_IRUGO, root,
				&zcache_last_active_anon_pageframes);
	zdfs("last_inactive_anon_pageframes", S_IRUGO, root,
				&zcache_last_inactive_anon_pageframes);
	zdfs("eph_nonactive_puts_ignored", S_IRUGO, root,
				&zcache_eph_nonactive_puts_ignored);
	zdfs("pers_nonactive_puts_ignored", S_IRUGO, root,
				&zcache_pers_nonactive_puts_ignored);
	zdfs64("eph_zbytes", S_IRUGO, root, &zcache_eph_zbytes);
	zdfs64("eph_zbytes_max", S_IRUGO, root, &zcache_eph_zbytes_max);
	zdfs64("pers_zbytes", S_IRUGO, root, &zcache_pers_zbytes);
	zdfs64("pers_zbytes_max", S_IRUGO, root, &zcache_pers_zbytes_max);
	return 0;
}
#undef	zdebugfs
#undef	zdfs64

/* developers can call this in case of ooms, e.g. to find memory leaks */
void zcache_dump(void)
{
	pr_debug("zcache: obj_count=%u\n", zcache_obj_count);
	pr_debug("zcache: obj_count_max=%u\n", zcache_obj_count_max);
	pr_debug("zcache: objnode_count=%u\n", zcache_objnode_count);
	pr_debug("zcache: objnode_count_max=%u\n", zcache_objnode_count_max);
	pr_debug("zcache: flush_total=%u\n", zcache_flush_total);
	pr_debug("zcache: flush_found=%u\n", zcache_flush_found);
	pr_debug("zcache: flobj_total=%u\n", zcache_flobj_total);
	pr_debug("zcache: flobj_found=%u\n", zcache_flobj_found);
	pr_debug("zcache: failed_eph_puts=%u\n", zcache_failed_eph_puts);
	pr_debug("zcache: failed_pers_puts=%u\n", zcache_failed_pers_puts);
	pr_debug("zcache: failed_get_free_pages=%u\n",
				zcache_failed_getfreepages);
	pr_debug("zcache: failed_alloc=%u\n", zcache_failed_alloc);
	pr_debug("zcache: put_to_flush=%u\n", zcache_put_to_flush);
	pr_debug("zcache: compress_poor=%u\n", zcache_compress_poor);
	pr_debug("zcache: mean_compress_poor=%u\n",
				zcache_mean_compress_poor);
	pr_debug("zcache: eph_ate_tail=%u\n", zcache_eph_ate_tail);
	pr_debug("zcache: eph_ate_tail_failed=%u\n",
				zcache_eph_ate_tail_failed);
	pr_debug("zcache: pers_ate_eph=%u\n", zcache_pers_ate_eph);
	pr_debug("zcache: pers_ate_eph_failed=%u\n",
				zcache_pers_ate_eph_failed);
	pr_debug("zcache: evicted_eph_zpages=%u\n", zcache_evicted_eph_zpages);
	pr_debug("zcache: evicted_eph_pageframes=%u\n",
				zcache_evicted_eph_pageframes);
	pr_debug("zcache: eph_pageframes=%u\n", zcache_eph_pageframes);
	pr_debug("zcache: eph_pageframes_max=%u\n", zcache_eph_pageframes_max);
	pr_debug("zcache: pers_pageframes=%u\n", zcache_pers_pageframes);
	pr_debug("zcache: pers_pageframes_max=%u\n",
				zcache_pers_pageframes_max);
	pr_debug("zcache: eph_zpages=%u\n", zcache_eph_zpages);
	pr_debug("zcache: eph_zpages_max=%u\n", zcache_eph_zpages_max);
	pr_debug("zcache: pers_zpages=%u\n", zcache_pers_zpages);
	pr_debug("zcache: pers_zpages_max=%u\n", zcache_pers_zpages_max);
	pr_debug("zcache: eph_zbytes=%llu\n",
				(unsigned long long)zcache_eph_zbytes);
	pr_debug("zcache: eph_zbytes_max=%llu\n",
				(unsigned long long)zcache_eph_zbytes_max);
	pr_debug("zcache: pers_zbytes=%llu\n",
				(unsigned long long)zcache_pers_zbytes);
	pr_debug("zcache: pers_zbytes_max=%llu\n",
			(unsigned long long)zcache_pers_zbytes_max);
}
#endif
