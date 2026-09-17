# Primera vez
python3 eduroam-linux-UdC-eduroam.py

mover el credencial .pem a ~/.config/eduroam/udc-eduroam-ca.pem (coger el credencial de el .py, empieza por -----BEGIN CERTIFICATE----- y termina por -----END CERTIFICATE-----, incluir todo)

En la terminal con nmcli

nmcli connection modify eduroam 802-1x.ca-cert "/home/fraga/.config/eduroam/udc-eduroam-ca.pem"
nmcli connection modify eduroam 802-1x.password "TUCONTRASEÑA"
nmcli connection modify eduroam 802-1x.password-flags 0
nmcli connection up eduroam
nmcli connection modify eduroam 802-1x.password-flags 1

# Siguientes veces
nmcli connection up eduroam

No sale como conectado
