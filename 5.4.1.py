from netmiko import ConnectHandler

myserver = {
    'device_type': 'linux',
    'host':   '192.168.56.103',  #Your Server IP
    'username': 'imranssh', #your Server Username
    'password': 'yan0707', #your server password
    'port' : 22,
    'secret': '',
}

net_connect = ConnectHandler(**myserver)
output = net_connect.send_command(' sudo apt-get update ')
print(output)
