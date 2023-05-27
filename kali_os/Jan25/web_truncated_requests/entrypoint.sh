#!/bin/ash

# Secure entrypoint
chmod 600 /entrypoint.sh

# Initialize & Start MariaDB
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld
mysql_install_db --user=mysql --ldata=/var/lib/mysql
mysqld --user=mysql --console --skip-name-resolve --skip-networking=0 &

# Wait for mysql to start
while ! mysqladmin ping -h'localhost' --silent; do echo "not up" && sleep .2; done

ADMINPASS=$(echo $RANDOM | md5sum | head -c 32)
FLAG=$(cat /flag.txt)

mysql -u root << EOF
CREATE DATABASE purchasedb;

CREATE TABLE purchasedb.requestlist (
    id INT NOT NULL AUTO_INCREMENT,
    product varchar(256) NOT NULL,
    receiver varchar(256) NOT NULL,
    location varchar(256) NOT NULL,
    approved int NOT NULL,
    PRIMARY KEY (id)
);

INSERT INTO purchasedb.requestlist(product, receiver, location, approved) VALUES
    ('Plantronics - Voyager 5200 UC (Poly) - Bluetooth Single-Ear (Monaural) Headset', 'Elaina Love', 'Houston', 1),
    ('LENTION USB C Hub Ethernet Adapter', 'Jarrett Pace', 'Dallas', 1),
    ('Plantronics Voyager 5200 Bluetooth Headset', 'Kristin Vang', 'Austin', 1),
    ('Razer Pro Type Ultra Wireless Mechanical Keyboard', 'Jaslyn Huerta', 'Amarillo', 1),
    ('Razer Kiyo Pro Streaming Webcam', 'Aracely Monroe', 'El Paso', 1),
    ('Sceptre 24" Professional Thin 75Hz 1080p LED Monitor', 'Sinthea Ryverin', 'Austin', 1),
    ('Hot Wheels: Volkswagen Beach Bomb toys', 'Eric Cameron', 'San Antonio', 0),
    ('${FLAG}', 'HTBbot', 'HTBer', 0);

CREATE TABLE purchasedb.users (
    id INT NOT NULL AUTO_INCREMENT,
    username varchar(34) NOT NULL,
    password varchar(34) NOT NULL,
    PRIMARY KEY (id)
);

INSERT INTO purchasedb.users (username, password) VALUES
    ('admin', '${ADMINPASS}');

GRANT ALL PRIVILEGES ON purchasedb.* TO 'purchaseUser'@'%' IDENTIFIED BY 'rh0x01';
FLUSH PRIVILEGES;
EOF

/usr/bin/supervisord -c /etc/supervisord.conf
