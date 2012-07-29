package com.anavi.location2sms;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.URLEncoder;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

public class UrlShortener 
{
	private String m_sShortUrl = "";
	
	UrlShortener()
	{
		
	}
	//------------------------------------------------------------------------------
	
	/**
     * Request short URL from Google API
     *
     * @param sURL
     *
     * @return nothing
	 * @throws IOException 
	 * @throws ClientProtocolException 
     */
	public void requestShortUrl(String sURL) throws ClientProtocolException, IOException
	{
		String sReqUrl = "http://is.gd/create.php?format=simple&longurl=";
		sReqUrl += URLEncoder.encode(sURL, "UTF-8");
		HttpGet httpReq = new HttpGet(sReqUrl);
		HttpClient httpclient = new DefaultHttpClient();
		HttpResponse response = httpclient.execute(httpReq);
		StatusLine statusLine = response.getStatusLine();
		if(HttpStatus.SC_OK == statusLine.getStatusCode())
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			response.getEntity().writeTo(out);
			out.close();
			m_sShortUrl = out.toString();
		}
		else
		{
		    //Closes the connection.
		    response.getEntity().getContent().close();
		    throw new IOException(statusLine.getReasonPhrase());
		}
	}
	//------------------------------------------------------------------------------

	/**
     * Get address
     *
     * @return QString
     */
	public String getShortUrl()
	{
	   return m_sShortUrl;
	}
	//------------------------------------------------------------------------------

}
