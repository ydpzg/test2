package com.example.mytest0126;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;


public class MainActivity extends Activity {
	private Button button_close1, button_close2, button_send1, button_send2, button_connect1, button_connect2;
	private int i = 0, j = 0;
	private boolean isRunning1 = false,  isRunning2 = false;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button_connect1 = (Button) findViewById(R.id.button_connect1);
        Button button_connect2 = (Button) findViewById(R.id.button_connect2);
        Button button_send1 = (Button) findViewById(R.id.button_send1);
        Button button_send2 = (Button) findViewById(R.id.button_send2);
        Button button_close1 = (Button) findViewById(R.id.button_close1);
        Button button_close2 = (Button) findViewById(R.id.button_close2);
        
        button_connect1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				JNI.connect1(1000);
				i = 0;
				isRunning1 = true;
			}
		});
        button_connect2.setOnClickListener(new OnClickListener() {
        	
        	@Override
        	public void onClick(View v) {
        		// TODO Auto-generated method stub
        		JNI.connect2(1000);
        		j = 0;
        		isRunning2 = true;
        	}
        });
        
        button_send1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
				new Thread(new Runnable() {
					
					@Override
					public void run() {
						// TODO Auto-generated method stub
						while(isRunning1 && i < 100000) {
							JNI.sendToServer1("我们dd11++==@#$" + i);
							i++;
							try {
								Thread.sleep(20);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}
				}).start();
			}
		});
        button_send2.setOnClickListener(new OnClickListener() {
        	
        	@Override
        	public void onClick(View v) {
        		// TODO Auto-generated method stub
        		new Thread(new Runnable() {
        			
        			@Override
        			public void run() {
        				// TODO Auto-generated method stub
        				while(isRunning2 && j < 100000) {
        					JNI.sendToServer2("品牌dd22--$#@5623*" + j);
        					j++;
        					try {
								Thread.sleep(20);
							} catch (InterruptedException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
        				}
        				j = 0;
        			}
        		}).start();
        	}
        });
        button_close1.setOnClickListener(new OnClickListener() {
        	
        	@Override
        	public void onClick(View v) {
        		// TODO Auto-generated method stub
        		JNI.closeConnection1();
        		isRunning1 = false;
        	}
        });
        button_close2.setOnClickListener(new OnClickListener() {
        	
        	@Override
        	public void onClick(View v) {
        		// TODO Auto-generated method stub
        		JNI.closeConnection2();
        		isRunning2 = false;
        	}
        });
    }
    
    @Override
    protected void onDestroy() {
    	// TODO Auto-generated method stub
    	super.onDestroy();
    	JNI.closeConnection1();
    	isRunning1 = false;
    	JNI.closeConnection2();
    	isRunning2 = false;
    }
}
