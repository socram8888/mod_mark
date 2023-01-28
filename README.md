
mod_mark
========

Apache 2 module for retrieving connections's SO_MARK.

This module defines a new environment variable called SOCKET_MARK which can be accessed and
processed from PHP and other content processors.

Installation
------------

Apache's `apxs` module compiler must be available. On Debian this can be installed using:
```bash
sudo apt install apache-dev
```

Once available, the module can be built and installed using:
```bash
make
sudo make install
sudo service apache2 restart
```

Please note that for this to work, the `tcp_fwmark_accept` kernel flag must be set.

This change can be made temporarily for testing via:
```bash
sysctl net.ipv4.tcp_fwmark_accept=1
```

If desired, it can be made persistent by creating a configuration file:
```bash
cat <<'EOF' | sudo tee /etc/sysctl.d/50-accept-fwmark.conf
# Allow getsockopt(SO_MARK) to fetch netfilter-assigned marks
net.ipv4.tcp_fwmark_accept = 1
EOF
sudo sysctl -p /etc/sysctl.d/50-accept-fwmark.conf
```
