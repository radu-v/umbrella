#!/system/bin/sh 

if [ ! -f /sbin/recovery ]; then
  # Setup swap
#  while [ ! -e /dev/block/vbswap0 ]; do
#    sleep 1
#  done
#  if ! grep -q vbswap /proc/swaps; then
#    # 1GB
#    echo 1073741824 > /sys/devices/virtual/block/vbswap0/disksize
#    echo 160 > /proc/sys/vm/swappiness

#    mkswap /dev/block/vbswap0
#    swapon /dev/block/vbswap0
#    echo "umod: vbswap initialized" > /dev/kmsg
#  fi
fi

# Remove unused swapfile
rm -f /data/vendor/swap/swapfile 2>/dev/null
sync

# Wait to set proper init values
sleep 30
