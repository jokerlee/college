/* ===================================================================== 
 * a) print the type of cpu
 * b) print the kernel version
 * c) print the the system uptime(in day/hour/minutes format)
 * d) print how many cputime have spent in user mode, monitor mode and idle
 * e) print used memory amount
 * f) print free memory amount
 * g) print number of i/o request
 * h) print number of context switch
 * i) print number of process created
 * ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define BF_SIZE 8192
#define STR_MAX 1024
#define HZ 200

struct cpu_stat {
    unsigned long procs;
    unsigned long long sys,
                       user, 
                       idle, 
                       ctxt;
};


struct cpu_stat cs;


/* print the type of cpu */
void read_cpu_type(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;

    if ((fp = fopen("/proc/cpuinfo", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/proc/cpuinfo", strerror(errno));
		exit(2);
    }

    do {
        fgets(buf, BF_SIZE, fp);
    } while (strncmp(buf, "model name", 10) != 0);
    fprintf(stdout, "cpu type\t: %s", buf + 13);
    
    fclose(fp);
}

/* print the kernel version */
void read_kernel_version(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;
    
    if ((fp = fopen("/proc/version", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/proc/version", strerror(errno));
		exit(2);
    }

    fgets(buf, BF_SIZE, fp);
    fprintf(stdout, "kernel version\t: %s", buf);
    
    fclose(fp);
}

/* print the the system uptime(in day/hour/minutes format) */
void read_uptime(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;
    unsigned long long tval;
    struct tm * ts;
   
    if ((fp = fopen("/proc/uptime", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/proc/uptime", strerror(errno));
		exit(2);
    }

    fscanf(fp, "%llu", &tval);
    fclose(fp);

    fprintf(stdout, "system uptime\t: %llu days %llu hours %llu minutes\n",
            tval/86400, (tval%86400)/3600, tval%60);
}

/* calculete how many cputime have spent in user mode, monitor mode and idle, 
 * how many processes created and number of context swtich upnow */
void read_cpu_stat(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;
    unsigned long long user,
                       sys,
                       idle, 
                       iowait, 
                       hardirq, 
                       softirq;

    if ((fp = fopen("/proc/stat", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/proc/stat", strerror(errno));
		exit(2);
    
    }
    /* from the code of sysstat */
	while (fgets(buf, 8192, fp) != NULL) {
		if (!strncmp(buf, "cpu ", 4)) {
			sscanf(buf + 5, "%llu %*llu %llu %llu %llu %llu %llu %*llu %*llu",
			       &user, /* &nice, */ &sys, &idle, &iowait, &hardirq, &softirq /* ,&steal, &guest */ );
        }
        
        if (!strncmp(buf, "ctxt ", 5)) {
            sscanf(buf + 5, "%llu", &cs.ctxt);
        } 
        
        if (!strncmp(buf, "processes ", 10)) {
            sscanf(buf + 10, "%ld", &cs.procs);
        } 
    }
    fclose(fp);
    
    cs.user = user;
    cs.idle = idle + iowait;
    cs.sys = sys + hardirq + softirq;
    
    fprintf(stdout, "cpu time\t: %llus user mode, %llus kernel mode, %llus idle\n",
            cs.user/HZ, cs.sys/HZ, cs.idle/HZ);
    fprintf(stdout, "processes\t: %ld\n", cs.procs);
    fprintf(stdout, "context switch\t: %llu\n", cs.ctxt);
}

 /* print used/free memory amount */
void read_mem_stat(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;
    unsigned long val = 0,
                  total = 0,
                  freed = 0;

    if ((fp = fopen("/proc/meminfo", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/proc/meminfo", strerror(errno));
		exit(2);
    }

    do {
        fscanf(fp, "%s %lu %*[^\n]", buf, &val);
        if (!strcmp(buf, "MemFree:") || !strcmp(buf, "Cached:")
                || !strcmp(buf, "Buffers:"))
            freed += val;

        if (strcmp(buf, "MemTotal:") == 0)
            total = val;
    } while (!feof(fp));
    
    fclose(fp); 
    fprintf(stdout, "memory info\t: %lu kB free, %lu kB used\n", 
            freed, total - freed);
}  

/* print number of i/o request */
void read_io_stat(void)
{
    char buf[BF_SIZE + 1];
    FILE * fp;
    unsigned long reads = 0,
                  writes = 0;

    if ((fp = fopen("/sys/block/sda/stat", "r")) == NULL) {
		fprintf(stderr, "Cannot open %s: %s\n", "/sys/block/sda/stat", strerror(errno));
		exit(2);
    }

    fgets(buf, BF_SIZE, fp);
    fclose(fp);

    sscanf(buf, "%*lu %*lu %lu %*lu %*lu %*lu %lu", &reads, &writes);
    
    fprintf(stdout, "io requests\t: %lu reads, %lu writes\n", reads, writes);
}

int main(int argc, char * argv[])
{
    read_cpu_type();
    read_kernel_version();
    read_uptime();
    read_cpu_stat();
    read_mem_stat();
    read_io_stat();
    
    return 0;
}
