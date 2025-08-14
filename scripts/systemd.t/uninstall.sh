sudo systemctl stop test_nooo.service || true
sudo rm /etc/systemd/system/test_nooo.service 
sudo systemctl daemon-reload
