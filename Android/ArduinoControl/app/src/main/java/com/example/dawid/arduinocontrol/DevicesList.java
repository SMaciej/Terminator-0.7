package com.example.dawid.arduinocontrol;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.widget.TextView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.Set;

public class DevicesList extends ActionBarActivity {

    //widgety
    Button buttonPaired;
    ListView devicesList;


    //bluetooth
    private BluetoothAdapter btAdapter = null;
    private Set<BluetoothDevice> pairedDevices;
    public static String myDevice_ADDRESS = "device_address";


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_devices_list);

        buttonPaired = (Button)findViewById(R.id.button);
        devicesList = (ListView)findViewById(R.id.listView);

        //jesli jest modul BT
        btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter == null)
        {
            //informacja o braku modułu Bluetooth
            Toast.makeText(getApplicationContext(), "Brak modułu Bluetooth", Toast.LENGTH_LONG).show();

            //koniec
            finish();
        }
        else if(!btAdapter.isEnabled())
        {
            //Poproś użytkownika o włączenie BlueTooth
            Intent turnBTon = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnBTon,1);
        }

        buttonPaired.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                listOfPairedDevices();
            }
        });

    }

    private void listOfPairedDevices()
    {
        pairedDevices = btAdapter.getBondedDevices();
        ArrayList list = new ArrayList();

        if (pairedDevices.size()>0)
        {
            for(BluetoothDevice bt : pairedDevices)
            {
                list.add(bt.getName() + "\n" + bt.getAddress()); //wyciaga nazwy urzadzen
            }
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Brak sparowanych urządzeń.", Toast.LENGTH_LONG).show();
        }

        final ArrayAdapter adapter = new ArrayAdapter(this,android.R.layout.simple_list_item_1, list);
        devicesList.setAdapter(adapter);
        devicesList.setOnItemClickListener(myListClickListener); //po kliknieciu polaczenia

    }

    private AdapterView.OnItemClickListener myListClickListener = new AdapterView.OnItemClickListener()
    {
        public void onItemClick (AdapterView<?> av, View v, int arg2, long arg3)
        {
            // wyciaga adres MAC urządzenia
            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);


            Intent i = new Intent(DevicesList.this, arduinoControl.class);

            //przejscie do drugiego layout
            i.putExtra(myDevice_ADDRESS, address); //przesłanie do drugiego layout
            startActivity(i);
        }
    };


    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_devices_list, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}

