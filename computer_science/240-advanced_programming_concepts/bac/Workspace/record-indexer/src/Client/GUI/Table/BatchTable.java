package Client.GUI.Table;

import javax.swing.*;

import Client.Controller;

@SuppressWarnings("serial")
public class BatchTable extends JPanel
 {
	// Instance attributes used in this example
	public JTable table;
	private	JScrollPane scrollPane;
	String columnNames[];
	String dataValues[][];

	// Constructor of main frame
	public BatchTable()
	{
		this.setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
		this.setPreferredSize(Controller.client.getWindow().bottomLeft.getPreferredSize());

		String[] columns;
		columns = Controller.batch.getFTitleList();
		columnNames = new String[columns.length+1];
		dataValues = new String[Controller.batch.getRecordCount()][columns.length+1];
		
		for (int i = 0; i < Controller.batch.getRecordCount(); i++)
		{
			for (int j = 0; j < columns.length+1; j++)
			{
				if (i == 0)
				{
					if (j == 0)
					{
						columnNames[j] = "Record Number";
					}
					else
					{
						columnNames[j] = columns[j-1];
					}
				}
				if (j == 0)
				{
					dataValues[i][j] = (new Integer(i+1)).toString();
				}	
				else
				{
					dataValues[i][j] = "";
				}
			}
		}
		
		// Create a new table instance
		table = new JTable( dataValues, columnNames )
		{
			  public boolean isCellEditable(int row,int column)
			  {
				    if(column == 0) return false;//the 4th column is not editable
				    return true;
			  }
			  public boolean getScrollableTracksViewportWidth()
			  {
				  return false;
			  }
			  
			  
		};
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setCellSelectionEnabled(true);
		table.setPreferredSize(this.getPreferredSize());
		scrollPane = new JScrollPane(table, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
			    JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scrollPane.setPreferredSize(this.getPreferredSize());
		
		add(scrollPane);
	}

}