package com.example.androiddesign;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ShowTH extends Activity {
    Button button;
    String usrname,welcome;
    static String temp,humi;
    TextView textname,tempValue,humiValue;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.show_th);
        Intent intent = getIntent();
        usrname = intent.getStringExtra("name");
        button = (Button)findViewById(R.id.update);
        button.setOnClickListener(new button_click());
        tempValue = (TextView)findViewById(R.id.temperature);
        humiValue = (TextView)findViewById(R.id.humidity);
        textname = (TextView)findViewById(R.id.welcome);
        welcome = "Welcome "+usrname+" !";
        textname.setText(welcome);

    }
    class button_click implements View.OnClickListener{
        @Override
        public void onClick(View v){
            new Thread(new Runnable() {
                @Override
                public void run() {

                    try{
                        Socket socket = new Socket("172.20.10.3",8000);

                        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream(),"utf-8"));
                        temp = bufferedReader.readLine();
                        humi = bufferedReader.readLine();

                        bufferedReader.close();
                        socket.close();

                    }catch (IOException e){
                        e.printStackTrace();
                    }

                }
            }).start();

            tempValue.setText(temp);
            humiValue.setText(humi);

        }
    }

}
