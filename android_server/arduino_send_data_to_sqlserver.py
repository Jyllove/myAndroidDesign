from pymysql import connect
from time import sleep
import socket
import re
import datetime

def main():
    conn = connect(
        host="localhost",
        port=3306,
        user="android",
        password="123456",
        database="android_design",
        charset="utf8"
    )
    cs = conn.cursor()
    tcp_server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_server_socket.bind(("", 9000))
    tcp_server_socket.listen(128)
    new_client_socket, client_addr = tcp_server_socket.accept()
    while True:
        a = new_client_socket.recv(1024).decode("utf8")
        nowTime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        data = re.sub(r',',' ',a)
        data = data.split()
        print(nowTime)
        print(data)
        #print(nowTime+" "+data)
        sql = "update device set temp=%s,humi=%s where id=1"

        cs.execute(sql,data)
        conn.commit()



    cs.close()
    conn.close()




if __name__ == '__main__':
    main()