package com.anavi.location2sms;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Locale;

import org.apache.http.client.ClientProtocolException;

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
	private static boolean m_bPlaybook = false;

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
	
	private UrlShortener m_urlShortener;
	
	private Bitmap m_imageMap = null;
	
	private Handler m_handler = null;
	
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
 		m_sBestProvider = (true == m_bPlaybook) ? "gps" : m_locationManager.getBestProvider(new Criteria(), false);
 		
 		boolean bIsTablet = getResources().getBoolean(R.bool.isTablet);
 		double nMapCoefLandscape = 0.52;
 		double nMapCoefPortrait = 0.65;
 		if (true == bIsTablet)
 		{
 			nMapCoefLandscape = 0.72;
 			nMapCoefPortrait = 0.75;
 		}
 		
 		m_ImageMap = (ImageView) findViewById(R.id.image_map);
 		Display display = getWindowManager().getDefaultDisplay();
 		m_nMapWidth = display.getWidth();
 		if (display.getWidth() >= display.getHeight())
 		{
 			//landscape
 			m_nMapHeight = (int)(nMapCoefLandscape*display.getHeight());
 		}
 		else
 		{
 			//portrait
 			m_nMapHeight = (int)(nMapCoefPortrait*display.getHeight());
 		}
 		
 		m_mapZoomSlider = (SeekBar)findViewById(R.id.map_zoom_slider);
 		m_mapZoomSlider.setOnSeekBarChangeListener(this);
 		m_mapZoomSlider.setMax(18);
 		
 		m_urlShortener = new UrlShortener();
 		
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
            	Intent sendIntent = null;
            	if (true == m_bPlaybook)
            	{
            		sendIntent = new Intent(Intent.ACTION_SEND);
            		sendIntent.setType("text/plain");
            	}
            	else
            	{
            		sendIntent = new Intent(Intent.ACTION_VIEW);
            		sendIntent.setData(Uri.parse("mailto:"));
            	}
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
 		positionUpdated();
    }
	//------------------------------------------------------------------------------

    /** Register for the updates when Activity is in foreground */
	@Override
	protected void onResume() 
	{
		super.onResume();
		m_locationManager.requestLocationUpdates(m_sBestProvider, 20000, 1, this);
	}
	//------------------------------------------------------------------------------

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
	
	/**
	 * Compose message
	 * 
	 * @param bIsEmail message type
	 * @return message
	 */
	private String composeMessageContent(boolean bIsEmail)
	{
		if (null == m_location)
		{
			return "";
		}
		String sLocation = "";
		if (0 < m_sAddress.length())
        {
            sLocation += getString(R.string.main_address) + m_sAddress + "\n";
        }
        sLocation += getString(R.string.main_latitude);
        sLocation += String.format(" %.5f", m_location.getLatitude());
        sLocation += "\n";
        sLocation += getString(R.string.main_longitude);
        sLocation += String.format(" %.5f", m_location.getLongitude());
        sLocation += "\n";

        //Add short URL to map if available
        if (null != m_urlShortener)
        {
        	String sShortUrl = m_urlShortener.getShortUrl();
        	if (0 < sShortUrl.length())
        	{
        		sLocation += sShortUrl;
        	}
        }

        //Append app signature to e-mails
        if (true == bIsEmail)
        {
            sLocation += "\n";
            
            sLocation += String.format(getString(R.string.main_sent_from), m_sAppName);
        }
		return sLocation;
	}
	//------------------------------------------------------------------------------

	public void onLocationChanged(Location location) 
	{
		m_location = location;
		positionUpdated();
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

	/**
	 * Load new location data
	 * 
	 * @return nothing
	 */
	private void positionUpdated() 
	{
		if (null == m_location)
		{
			return;
		}
		
		m_labelCoordinates = (TextView) findViewById(R.id.labelCoordinates);
				
		final ReverseGeocoding reverseGeocoder = new ReverseGeocoding();
				
		m_handler = new Handler() 
		{
			public void handleMessage(Message msg) 
			{
				switch(msg.what)
				{
					case 1:
						loadAddress();
						loading(false);
					break;
					case 2:
						m_ImageMap.setImageBitmap(m_imageMap);
						m_ImageMap.setVisibility(View.VISIBLE);
					break;
					case 3:
						m_ImageMap.setVisibility(View.GONE);
					break;
				}
			}
			
		};
		
		//start new threads for retrieving information
		loadAddress(reverseGeocoder);
		String sMapUrl = getMapUrl(m_mapZoomSlider.getProgress(), 
									m_nMapWidth, m_nMapHeight);
		loadMap(sMapUrl);
		loadMapShortUrl();
	}
	//------------------------------------------------------------------------------

	/**
	 * Retrieve short URL to the map
	 * 
	 * @return nothing
	 */
	private void loadMapShortUrl()
	{
		try 
		{
			m_urlShortener.requestShortUrl(getMapUrl(14, 400, 400));
		} catch (ClientProtocolException e) 
		{
			//Nothing to do
		} 
		catch (IOException e) 
		{
			//Nothing to do
		}
	}
	//------------------------------------------------------------------------------

	/**
	 * Download map and fire a signal to load it
	 * 
	 * @param sUrl URL to the map
	 * @return nothing
	 */
	private void loadMap(final String sUrl)
	{
		Thread threadLocationData = new Thread() 
		{  
			public void run() 
			{
				if (0 < sUrl.length())
				{
					try 
					{
						URL url = new URL(sUrl);
						m_imageMap = BitmapFactory.decodeStream(
										url.openConnection().getInputStream());
						m_handler.sendEmptyMessage(2);
					} 
					catch (MalformedURLException e) 
					{
						//nothing to do
						m_handler.sendEmptyMessage(3);
					}
					catch (IOException e) 
					{
						//nothing to do
						m_handler.sendEmptyMessage(3);
					}
				}
				else
				{
					//Unable to load image
					m_handler.sendEmptyMessage(3);
				}

			}
		};
		threadLocationData.start();
	}
	//------------------------------------------------------------------------------

	/**
	 * Download XML and retrieve address from geo coordinates
	 * 
	 * @param reverseGeocoder
	 */
	private void loadAddress(final ReverseGeocoding reverseGeocoder)
	{
		Thread threadLocationData = new Thread() 
		{  
			public void run() 
			{
				try 
				{
					//download data
					reverseGeocoder.getGeoDataOverHttp(m_location.getLatitude(), 
							m_location.getLongitude());
					//parse data and retrieve address
					reverseGeocoder.loadAddress();
					//save address
					m_sAddress = reverseGeocoder.getAddress();
					//emit a signal to show the address
					m_handler.sendEmptyMessage(1);
				} 
				catch (IOException e) 
				{
					//Nothing to do
				}

			}
		};
		threadLocationData.start();
	}
	//------------------------------------------------------------------------------

	/**
	 * Get URL to static map
	 * 
	 * @param nZoom zoom level
	 * @param nMapWidth map width
	 * @param nMapHeight map height
	 * @return Map URL
	 */
	private String getMapUrl(int nZoom, int nMapWidth, int nMapHeight)
	{
		String sCoord = String.format(Locale.ENGLISH, "%.5f,%.5f", m_location.getLatitude(), m_location.getLongitude());
		
		String sUrl = "http://maps.googleapis.com/maps/api/staticmap?center=";
        sUrl += sCoord;
        sUrl += "&zoom=";
        sUrl += nZoom;
        sUrl += "&size=";
        sUrl += nMapWidth;
        sUrl += "x";
        sUrl += nMapHeight;
        sUrl += "&sensor=false&markers=color:blue|label:O|";
        sUrl += sCoord;
		
        
        /*String sUrl = "http://m.nok.it/?app_id=";
        sUrl += "&token=";
        sUrl += "&c=";
        sUrl += sCoord;
        sUrl += "&z=";
        sUrl += nZoom;
        sUrl += "&h=";
        sUrl += nMapHeight;
        sUrl += "&w=";
        sUrl += nMapWidth;
        sUrl += "&nord";*/
		
        return sUrl;
	}
	//------------------------------------------------------------------------------

	/**
	 * get coordinated as formatted text
	 * 
	 * @return String
	 */
	private String getCoordinatesAsText()
	{
		if (null == m_location)
		{
			return "";
		}
	    String sText = getString(R.string.main_latitude_label);
	    sText += " <font color=\"#006BC2\">%.5f</font> ";
	    sText += getString(R.string.main_longitude_label);
	    sText += " <font color=\"#006BC2\">%.5f</font><br />";
	    return String.format(sText, m_location.getLatitude(), m_location.getLongitude());
	}
	//------------------------------------------------------------------------------

	private void loadAddress()
	{
		String sAddr = getCoordinatesAsText();
		if (0 < m_sAddress.length())
		{
			sAddr += getString(R.string.main_address_label);
			sAddr += String.format(" <font color=\"#006BC2\">%s</font>", m_sAddress);
		}
		m_labelCoordinates.setText(Html.fromHtml(sAddr), TextView.BufferType.SPANNABLE);
	}
	//------------------------------------------------------------------------------

	public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) 
	{
		//reload map
		if ( (null != m_location) && (null != m_handler) )
		{
			String sMapUrl = getMapUrl(m_mapZoomSlider.getProgress(), 
					m_nMapWidth, m_nMapHeight);
			loadMap(sMapUrl);
			//TODO: loadImage(getMapUrl(m_mapZoomSlider.getProgress(), m_nMapWidth, m_nMapHeight));
		}
	}
	//------------------------------------------------------------------------------

	public void onStartTrackingTouch(SeekBar seekBar) 
	{
		//Nothing to do
	}
	//------------------------------------------------------------------------------

	public void onStopTrackingTouch(SeekBar seekBar) 
	{
		//Nothing to do
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

	/**
	 * Show loading dialog
	 * 
	 * @param bStart start or stop
	 */
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