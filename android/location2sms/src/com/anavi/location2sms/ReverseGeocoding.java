package com.anavi.location2sms;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.StringReader;
import java.util.Locale;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import android.util.Xml;

public class ReverseGeocoding 
{
	private String m_sAddress = "";
	
	private String m_sData = "";
	
	ReverseGeocoding()
	{
		
	}
	
	public void loadAddress()
	{
		try 
		{	        
	    	//Parse XML file
	        XmlPullParser xpp = Xml.newPullParser();
	        StringReader reader = new StringReader(m_sData);
	        xpp.setInput(reader);
	        
			xpp.next();
			int eventType = xpp.getEventType();
			String sTagName = "";		
			while (eventType != XmlPullParser.END_DOCUMENT)
			{
				if (eventType == XmlPullParser.START_TAG)
				{
					sTagName =  xpp.getName();
				}
				else if (eventType == XmlPullParser.TEXT)
				{
					if (0 == sTagName.compareTo("formatted_address"))
					{
						m_sAddress = xpp.getText();
						break;
					}
				}
				
				eventType = xpp.next();
			}
			reader.close();
		} 
		catch (XmlPullParserException e) 
		{
			// Nothing to do
		} 
		catch (IOException e) 
		{
			// Nothing to do
		}
	}
	//------------------------------------------------------------------------------
	
	
	/**
	 * Send HTTP request and get product information
	 * 
	 * @param sUrl URL
	 * 
	 * @return boolean true on success
	 * @throws IOException
	 */
	public void getGeoDataOverHttp(double nLatitude, double nLongitude) throws IOException
	{	
		String sUrl = "http://maps.googleapis.com/maps/api/geocode/";
		sUrl += "xml?latlng=";
		sUrl += String.format(Locale.ENGLISH, "%.5f,%.5f", nLatitude, nLongitude);
		sUrl += "&sensor=false";
		HttpGet httpReq = new HttpGet(sUrl);
		HttpClient httpclient = new DefaultHttpClient();
		HttpResponse response = httpclient.execute(httpReq);
		StatusLine statusLine = response.getStatusLine();
		if(HttpStatus.SC_OK == statusLine.getStatusCode())
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			response.getEntity().writeTo(out);
			out.close();
			m_sData = out.toString();
		}
		else
		{
		    //Closes the connection.
		    response.getEntity().getContent().close();
		    throw new IOException(statusLine.getReasonPhrase());
		}
	}
	//------------------------------------------------------------------------------
	
	public String getAddress()
	{
		return m_sAddress;
	}
}
