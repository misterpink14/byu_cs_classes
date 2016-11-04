package Client.GUI.ImageSupport;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;

import Client.Controller;

@SuppressWarnings("serial")
public class ImageNavigationView extends JPanel
{
	public JLayeredPane layer;
	public ImageIcon ii;
	public ImageNavigationView()
	{
		super();
		initUI();
	}
	
	private void initUI()
	{
		this.setBackground(Color.GRAY);
		this.setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
	}
	
	public void insertImage(String imageUrl)
	{
		this.setSize(this.getPreferredSize());
		double wScale = (double)Controller.client.getWindow().top.getWidth()/(double)Controller.client.getWindow().top.getHeight();
		double hScale = (double)Controller.client.getWindow().top.getHeight()/(double)Controller.client.getWindow().top.getWidth();
		
		double wLocalScale = (double)this.getWidth()/(double)this.getHeight();
//		double hLocalScale = (double)this.getHeight()/(double)this.getWidth();
		int width = 0;
		int height = 0;
		if (wScale < wLocalScale)
		{
			//use the width
			width =  this.getWidth();
			height = (int) ( this.getHeight() / hScale);
		}
		else
		{
			//use the height
			width =  (int) (this.getWidth() / hScale);
			height = (int) this.getHeight();
			
		}
		layer = new JLayeredPane();

		BufferedImage image = null;
		try {
			image = ImageIO.read(new URL(imageUrl));

		} catch (IOException e) {
			e.printStackTrace();
	    }
		
		ii = new ImageIcon(image);
		
		layer.setBounds(0,0,this.getWidth(), this.getHeight());

		Image newImage = ii.getImage().getScaledInstance(width, height,  java.awt.Image.SCALE_SMOOTH);
		ii.setImage(newImage);
		
		JLabel picLabel = new JLabel(ii);

		layer.setLayer(picLabel, Integer.valueOf(1));
		layer.add(picLabel);
		layer.setPreferredSize(this.getPreferredSize());
		add(layer);
//		add(picLabel);
		
		revalidate();
		repaint();
		
	}
}
