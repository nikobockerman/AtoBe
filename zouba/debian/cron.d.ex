#
# Regular cron jobs for the zouba package
#
0 4	* * *	root	[ -x /usr/bin/zouba_maintenance ] && /usr/bin/zouba_maintenance
