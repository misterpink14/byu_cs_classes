package Shared.Model;

/**
 * Record class. Holds record information.
 * 
 * @author Benjamin Thompson
 *
 */
public class Record extends Parent
{
	String value;
	Integer row;
	Integer imageID;
	Integer fieldID;
	
	/**
	 * Record Constructor
	 * 
	 * @param id
	 * @param value
	 * @param row
	 * @param fieldID
	 * @param imageID
	 */
	public Record(String value, Integer row, Integer imageID, Integer fieldID)
	{
		super(-1);
		this.value = value;
		this.row = row;
		this.fieldID = fieldID;
		this.imageID = imageID;
	}

	/**
	 * Returns value
	 * 
	 * @return the value
	 */
	public String getValue()
	{
		return value;
	}

	/**
	 * Sets value
	 * 
	 * @param value the value to set
	 */
	public void setValue(String value)
	{
		this.value = value;
	}

	/**
	 * Returns row
	 * 
	 * @return the row
	 */
	public Integer getRow()
	{
		return row;
	}

	/**
	 * Sets Row
	 * 
	 * @param row the row to set
	 */
	public void setRow(Integer row)
	{
		this.row = row;
	}

	/**
	 * Returns fieldID
	 * 
	 * @return the fieldID
	 */
	public Integer getFieldID()
	{
		return fieldID;
	}

	/**
	 * Sets fieldID
	 * 
	 * @param fieldID the fieldID to set
	 */
	public void setFieldID(Integer fieldID)
	{
		this.fieldID = fieldID;
	}

	/**
	 * Returns imageID
	 * 
	 * @return the imageID
	 */
	public Integer getImageID()
	{
		return imageID;
	}

	/**
	 * Sets imageID
	 * 
	 * @param imageID the imageID to set
	 */
	public void setImageID(Integer imageID)
	{
		this.imageID = imageID;
	}
	
}