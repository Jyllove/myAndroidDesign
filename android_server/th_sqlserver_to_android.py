from pymysql import connect
import socket

def main():
    while True:

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
        tcp_server_socket.bind(("", 8000))
        tcp_server_socket.listen(128)
        new_client_socket, client_addr = tcp_server_socket.accept()
        sql = "select temp,humi from device where id=1"
        count = cs.execute(sql)
        record = cs.fetchone()
        temp = record[0]
        humi = record[1]
        sendtemp = record[0]+"\r\n"
        sendhumi = record[1]+"\r\n"
        try:
            new_client_socket.send(sendtemp.encode("utf8"))
            new_client_socket.send(sendhumi.encode("utf8"))
            print("发送...")
            print("温度:"+temp+", 湿度:"+humi)
        except ConnectionAbortedError:
            print("disconnect!")

        tcp_server_socket.close()

        cs.close()
        conn.close()

if __name__ == '__main__':
    main()