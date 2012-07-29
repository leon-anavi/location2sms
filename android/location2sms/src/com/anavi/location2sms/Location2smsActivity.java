package com.anavi.location2sms;

import java.io.IOException;
import java.net.URL;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Html;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

public class Location2smsActivity extends Activity implements LocationListener, OnSeekBarChangeListener
{
	private static final String TAG = "l2m";
	private static final String[] S = { "Out of Service",
			"Temporarily Unavailable", "Available" };
	
	private boolean m_bIsPositionFound = false;

	private LocationManager m_locationManager;
	
	private String m_sBestProvider;
	
	private Location m_location  = null;
	
	private String m_sAddress = "";
	
	private ImageView m_ImageMap;
	
	private SeekBar m_mapZoomSlider;
	
	private int m_nMapWidth;

	private int m_nMapHeight;
	
	private TextView m_labelCoordinates;
	
	private static String m_sAppName = "location2sms";
	
	private ProgressDialog m_dialogWait = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //remove title and expand to full screen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
        		WindowManager.LayoutParams.FLAG_FULLSCREEN, 
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        setContentView(R.layout.main);
        
        loading(true);
            
    	// Get the location manager
 		m_locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
 		//get the best provider
 		m_sBestProvider = m_locationManager.getBestProvider(new Criteria(), false);
 		
 		m_ImageMap = (ImageView) findViewById(R.id.image_map);
 		Display display = getWindowManager().getDefaultDisplay();
 		m_nMapWidth = display.getWidth();
 		if (display.getWidth() >= display.getHeight())
 		{
 			//landscape
 			m_nMapHeight = (int)(0.55*display.getHeight());
 		}
 		else
 		{
 			//portrait
 			m_nMapHeight = (int)(0.66*display.getHeight());
 		}
 		
 		m_mapZoomSlider = (SeekBar)findViewById(R.id.map_zoom_slider);
 		m_mapZoomSlider.setOnSeekBarChangeListener(this);
 		m_mapZoomSlider.setMax(18);
 		
        //send location as SMS
        Button buttonMainLeft = (Button) findViewById(R.id.buttonMainLeft);
        if(false == getPackageManager().hasSystemFeature(PackageManager.FEATURE_TELEPHONY))
        {
        	//Hide the button if the device cannot send SMS
        	buttonMainLeft.setVisibility(View.GONE);
        }
        else
        {
	        buttonMainLeft.setOnClickListener(new View.OnClickListener() {
	            public void onClick(View v) {
	            	
	            	Intent sendIntent = new Intent(Intent.ACTION_VIEW);         
	            	sendIntent.setData(Uri.parse("sms:"));
	            	sendIntent.putExtra("sms_body", composeMessageContent(false));
	            	try 
	            	{
						startActivity(sendIntent);
					} 
	            	catch (ActivityNotFoundException e) 
					{
						//Nothing to do
					}
	            }
	        });
        }
		
        //send location as e-mail
        Button buttonMainRight = (Button) findViewById(R.id.buttonMainRight);
        buttonMainRight.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) 
            {
            	Intent sendIntent = new Intent(Intent.ACTION_VIEW);   
            	sendIntent.setData(Uri.parse("mailto:"));
            	sendIntent.putExtra(Intent.EXTRA_SUBJECT, m_sAppName);
            	sendIntent.putExtra(Intent.EXTRA_TEXT, composeMessageContent(true));
            	try 
            	{
					startActivity(sendIntent);
				} 
            	catch (ActivityNotFoundException e) 
				{
					//Nothing to do
				}
            }
        });

 		TextView labelApp = (TextView) findViewById(R.id.labelApp);
 		String sLabelAppText = "location<font color=\"#006BC2\">2</font>sms";
 		labelApp.setText(Html.fromHtml(sLabelAppText), TextView.BufferType.SPANNABLE);
 		
 		m_mapZoomSlider.setProgress(14);
 		
 		m_location = m_locationManager.getLastKnownLocation(m_sBestProvider);
 		printLocation();
    }
    
    /** Register for the updates when Activity is in foreground */
	@Override
	protected void onResume() 
	{
		super.onResume();
		m_locationManager.requestLocationUpdates(m_sBestProvider, 20000, 1, this);
	}

	/** Stop the updates when Activity is paused */
	@Override
	protected void onPause() 
	{
		super.onPause();
		m_locationManager.removeUpdates(this);
	}
	//------------------------------------------------------------------------------

	@Override public boolean onCreateOptionsMenu(Menu menu) 
	{
	    MenuInflater inflater = getMenuInflater();
	    inflater.inflate(R.menu.options, menu);
	    return true;
	}
	//------------------------------------------------------------------------------
	
	private String composeMessageContent(boolean bIsEmail)
	{
		if ( (null == m_location) || (false == m_bIsPositionFound) )
		{
			return "";
		}
		String sLocation = "";
		if (0 < m_sAddress.length())
        {
            sLocation += "Address: " + m_sAddress + "\n";
        }
        sLocation += "Latitude: ";
        sLocation += String.format("%.5f", m_location.getLatitude());
        sLocation += "\n";
        sLocation += "Longitude: ";
        sLocation += String.format("%.5f", m_location.getLongitude());
        sLocation += "\n";

        //TODO: Add URL to map if available

        //Append app signature to e-mails
        if (true == bIsEmail)
        {
            sLocation += "\n";
            sLocation += "Sent from ";
            sLocation += m_sAppName;
        }
		return sLocation;
	}
	//------------------------------------------------------------------------------

	public void onLocationChanged(Location location) 
	{
		m_bIsPositionFound = true;
		m_location = location;
		printLocation();
	}
	//------------------------------------------------------------------------------

	public void onProviderDisabled(String provider) 
	{
		// let okProvider be bestProvider
		// re-register for updates
	}
	//------------------------------------------------------------------------------

	public void onProviderEnabled(String provider) 
	{
		// is provider better than bestProvider?
		// is yes, bestProvider = provider
	}
	//------------------------------------------------------------------------------

	public void onStatusChanged(String provider, int status, Bundle extras) 
	{
		//Handle change of provider
	}
	//------------------------------------------------------------------------------

	private void printLocation() 
	{
		if (null == m_location)
		{
			return;
		}
		
		m_labelCoordinates = (TextView) findViewById(R.id.labelCoordinates);
		
		try
		{
			loadImage(getMapUrl());
		}
		catch (Exception e) 
		{
			//unable to load image
		}
		
		final ReverseGeocoding reverseGeocoder = new ReverseGeocoding();
		
		final Handler handler = new Handler() 
		{
			public void handleMessage(Message msg) 
			{
				if (0 == msg.what)
				{
					reverseGeocoder.loadAddress();
					m_sAddress = reverseGeocoder.getAddress();
					loadAddress();
				}
				loading(false);
			}
		};
		
		Thread checkUpdate = new Thread() 
		{  
			public void run() 
			{
				try 
				{
					reverseGeocoder.getGeoDataOverHttp(m_location.getLatitude(), 
														m_location.getLongitude());
					handler.sendEmptyMessage(0);
				} 
				catch (IOException e) 
				{
					handler.sendEmptyMessage(1);
				}
			}
		};
		checkUpdate.start();		
	}
	//------------------------------------------------------------------------------

	private String getMapUrl()
	{
		String sCoord = String.format("%.5f,%.5f", m_location.getLatitude(), m_location.getLongitude());
		
		String sUrl = "http://maps.googleapis.com/maps/api/staticmap?center=";
        sUrl += sCoord;
        sUrl += "&zoom=";
        sUrl += m_mapZoomSlider.getProgress();
        sUrl += "&size=";
        sUrl += m_nMapWidth;
        sUrl += "x";
        sUrl += m_nMapHeight;
        sUrl += "&sensor=false&markers=color:blue|label:O|";
        sUrl += sCoord;
        
        return sUrl;
	}
	//------------------------------------------------------------------------------

	private String getCoordinatesAsText()
	{
		if (null == m_location)
		{
			return "";
		}
	    String sText = "Latitude ";
	    sText += "<font color=\"#006BC2\">%.5f</font> ";
	    sText += "Longitude ";
	    sText += "<font color=\"#006BC2\">%.5f</font><br />";
	    return String.format(sText, m_location.getLatitude(), m_location.getLongitude());
	}
	//------------------------------------------------------------------------------

	private void loadAddress()
	{
		String sAddr = getCoordinatesAsText();
		if (0 < m_sAddress.length())
		{
			sAddr += "Address ";
			sAddr += String.format("<font color=\"#006BC2\">%s</font>", m_sAddress);
		}
		m_labelCoordinates.setText(Html.fromHtml(sAddr), TextView.BufferType.SPANNABLE);
	}
	//------------------------------------------------------------------------------

	/**
	 * load an external image by URL 
	 * 
	 * @param sUrl URL to the image
	 * 
	 * @return nothing
	 * @throws nothing
	 */
	private void loadImage(String sUrl)
	{
		try 
		{
			if (0 == sUrl.length())
			{
				//no image
				throw new IOException();
			}
			URL url = new URL(sUrl);
			Bitmap bmp = BitmapFactory.decodeStream(url.openConnection().getInputStream());
			m_ImageMap.setImageBitmap(bmp);
						
			m_ImageMap.setVisibility(View.VISIBLE);
		} 
		catch (IOException e) 
		{
			//hide the image
			m_ImageMap.setVisibility(View.GONE);
		}
	}
	//------------------------------------------------------------------------------
	
	public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) 
	{
		//reload map
		if (true == m_bIsPositionFound)
		{
			loadImage(getMapUrl());
		}
	}
	//------------------------------------------------------------------------------

	public void onStartTrackingTouch(SeekBar seekBar) 
	{
		
	}
	//------------------------------------------------------------------------------

	public void onStopTrackingTouch(SeekBar seekBar) 
	{
		
	}
	//------------------------------------------------------------------------------

	@Override public boolean onOptionsItemSelected(MenuItem item) 
	{
	    // Handle item selection
	    switch (item.getItemId()) 
	    {
	    case R.id.menu_about:
	    {
	    	Intent switchView = new Intent(this, AboutActivity.class);
            startActivityForResult(switchView, 0);
	    	return true;
	    }
	    default:
	        return super.onOptionsItemSelected(item);
	    }
	}
	//------------------------------------------------------------------------------

	private void loading(boolean bStart)
	{
		LinearLayout layoutMain = (LinearLayout) findViewById(R.id.layout_main);
		if (true == bStart)
		{
			layoutMain.setVisibility(View.GONE);
			m_dialogWait = ProgressDialog.show(this, "", "Please wait...", true);
		}
		else 
		{
			layoutMain.setVisibility(View.VISIBLE);
			if (null != m_dialogWait)
			{
				m_dialogWait.dismiss();
			}
		}
	}
	//------------------------------------------------------------------------------

}