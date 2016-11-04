package Client.GUI;

import java.awt.Dialog;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import Client.Controller;

@SuppressWarnings("serial")
public class DownloadBatchView extends JDialog
{
	JTextArea userText;
	JComboBox<String> cb;
	
	public DownloadBatchView()
	{
		initUI();
	}
		
	private void initUI()
	{
		setModalityType(Dialog.ModalityType.APPLICATION_MODAL);

		JPanel basic = new JPanel();
        basic.setLayout(new BoxLayout(basic, BoxLayout.Y_AXIS));
        add(basic);
        
        JPanel top = new JPanel();
        JPanel bottom = new JPanel();

        cb = new JComboBox<String>( Controller.getProjects() );
        
        userText = new JTextArea();
        userText.setEditable(false);

        userText.setText("Project: ");
        
        JButton viewSample = new JButton("View Sample");
        
        viewSample.addActionListener(new ActionListener()
        {
			@Override
			public void actionPerformed(ActionEvent e)
			{
				String imageUri = Controller.getSampleImage(cb.getSelectedIndex());
				new SampleImageView(imageUri);
			}
        });
        
        JButton cancel = new JButton("Cancel");
        cancel.addActionListener(new ActionListener()
        {
			@Override
			public void actionPerformed(ActionEvent e)
			{
				dispose();
			}
        });
        
        JButton download = new JButton("Download");
        download.addActionListener(new ActionListener()
        {
			@Override
			public void actionPerformed(ActionEvent e)
			{
				Controller.downloadBatch(cb.getSelectedIndex());
				dispose();
			}
        });
        
        bottom.add(cancel);
        bottom.add(download);
        
        top.add(userText);
        top.add(cb);
        top.add(viewSample);
        basic.add(top);
        basic.add(bottom);
        
        setTitle("Welcome to Indexer");
        setSize(400, 160);
        setLocationRelativeTo(null);
        setResizable(false);
        setAlwaysOnTop(true);
		setVisible(true);	
	}
	
	private class SampleImageView extends JDialog
	{
		private SampleImageView(String imageUri)
		{
			initUI(imageUri);
		}
		
		private void initUI(String imageUri)
		{
			setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
			JPanel basic = new JPanel();
	        basic.setLayout(new BoxLayout(basic, BoxLayout.Y_AXIS));
	        JPanel bottom = new JPanel();

			BufferedImage image = null;
			try {                
				image = ImageIO.read(new URL(imageUri));

			} catch (IOException e) {
				e.printStackTrace();
		    }
			
			ImageIcon ii = new ImageIcon(image);

			Image newImage = ii.getImage().getScaledInstance(600, 400,  java.awt.Image.SCALE_SMOOTH);
			ii.setImage(newImage);
			
			JButton close = new JButton("Close");
			close.addActionListener(new ActionListener()
	        {
				@Override
				public void actionPerformed(ActionEvent e)
				{
					dispose();
				}
	        });
			
			JLabel picLabel = new JLabel(ii);
			basic.add(picLabel);
			bottom.add(Box.createHorizontalGlue());
			bottom.add(close);
			bottom.add(Box.createHorizontalGlue());
			basic.add(bottom);
			add(basic);
			
			setSize(600, 500);
			setLocationRelativeTo(null);
	        setResizable(false);
	        setAlwaysOnTop(true);
			setVisible(true);
		}
	}

}
