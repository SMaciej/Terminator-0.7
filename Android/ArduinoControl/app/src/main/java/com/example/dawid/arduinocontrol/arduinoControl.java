package com.example.dawid.arduinocontrol;

/**
 * Created by Dawid on 07.01.2017.
 */
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;
import java.io.IOException;
import java.util.UUID;

public class arduinoControl extends ActionBarActivity {

    Button btnForward,
            btnBackward,
            btnDisconnect,
            btnLeft,
            btnRight,
            btnAutomatic,
            btnSensor,
            btnManual,
            btnStop;


    TextView textView;
    String adress = null;
    private ProgressDialog progress;
    BluetoothAdapter btAdapter = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    //uuid Jest to globalnie unikatowy identyfikator składający się z 32 liczb szesnastkowych
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        adress = newint.getStringExtra(DevicesList.myDevice_ADDRESS); //otrzymujemy adres modulu BT

        //layout od kontroli
        setContentView(R.layout.activity_arduino_control);

        btnStop = (Button) findViewById(R.id.button8);
        btnForward = (Button) findViewById(R.id.button2);
        btnBackward = (Button) findViewById(R.id.button3);
        btnDisconnect = (Button) findViewById(R.id.button4);
        btnLeft = (Button) findViewById(R.id.button6);
        btnRight = (Button) findViewById(R.id.button5);
        btnAutomatic = (Button) findViewById(R.id.button12);
        btnSensor = (Button) findViewById(R.id.button10);
        btnManual = (Button) findViewById(R.id.button11);
        textView = (TextView) findViewById(R.id.textView);

        new ConnectBT().execute();

        btnForward.setOnTouchListener(new View.OnTouchListener()
        {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN)
                {
                    goForward();
                    return true;
                }
                if (event.getAction()==MotionEvent.ACTION_UP)
                {
                    STOP();
                    return true;
                }
                    return false;
            }
        });
        btnBackward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    goBackward();
                    return true;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    STOP();
                    return true;
                }
                return false;
            }
        });

        btnLeft.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    turnLeft();
                    return true;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    STOP();
                    return true;
                }
                return false;
            }
        });

        btnRight.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    turnRight();
                    return true;
                }
                if (event.getAction() == MotionEvent.ACTION_UP) {
                    STOP();
                    return true;
                }
                return false;
            }
        });



        btnDisconnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DisconnectBT(); //rozlacz
            }
        });



        //how to move
        btnManual.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Manual(); //reczne
            }
        });

        btnSensor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Sensor(); //sensor
            }
        });

        btnAutomatic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Automatic(); //w prawo
            }
        });

        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                STOP(); //stop
            }
        });

    }


    private void goBackward()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("B".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void goForward()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("F".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void turnRight()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("R".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void turnLeft()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("L".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }


    private void DisconnectBT()
    {
        if (btSocket!=null) //spr czy socket jest zajety
        {
            try
            {
                btSocket.close(); //rozlacz
            }
            catch (IOException e)
            { message("Błąd");}
        }
        finish(); //powrot do poprzedniego widoku

    }

    private void Automatic()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("A".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void Sensor()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("S".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }


    private void Manual()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("M".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void STOP()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("O".toString().getBytes());
            }
            catch (IOException e)
            {
                message("Błąd");
            }
        }
    }

    private void message(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_arduino_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
/*
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_UP){
            switch (v.getId())
            {
                case R.id.button2:

                        goForward();


                    break;

                case R.id.button3:

                        goBackward();

                    break;

                case R.id.button6:

                        turnLeft();

                    break;

                case R.id.button5:

                        turnRight();

                    break;

            }

        }
        return true;
*/


    private class ConnectBT extends AsyncTask<Void, Void, Void>
    {
        private boolean Connected = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(arduinoControl.this, "Łączenie...", "Proszę czekać!!");
        }

        @Override
        protected Void doInBackground(Void... devices)
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                    btAdapter = BluetoothAdapter.getDefaultAdapter();//modul bt
                    BluetoothDevice dispositivo = btAdapter.getRemoteDevice(adress);//laczenie z urzadzenie i sprawdzenie czy polaczenie jest mozliwe
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//tworzenie RFCOMM (SPP) polaczenia
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();//rozpoczecie polaczenia
                }
            }
            catch (IOException e)
            {
                Connected = false;
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result)//sprawdz
        {
            super.onPostExecute(result);

            if (!Connected)
            {
                message("Nieudane połacznie. Czy urządzenie obsługuje protokół SPP? Spróbuj ponownie.");
                finish();
            }
            else
            {
                message("Połączono.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}

