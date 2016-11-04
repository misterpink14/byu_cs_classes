package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.List;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.DownloadBatch_Param;
import Shared.Communication.Result.DownloadBatch_Result;
import Shared.Model.Field;
import Shared.Model.Image;
import Shared.Model.Project;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class DownloadBatchHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		DownloadBatch_Param param = (DownloadBatch_Param)xs.fromXML(exchange.getRequestBody());
		DownloadBatch_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		Image i = new Image();
		Project p = new Project();
		p.setId(param.getProjectID());
		i.setProjectID(param.getProjectID());
		try
		{
			List<Field> fieldList = ServerFacade.downloadbatch(u, i, p);
			result = new DownloadBatch_Result(true, i.getId(), i.getProjectID(), i.getFile(), 
					p.getFirsty(), p.getHeight(), p.getRecords(), fieldList.size(), fieldList);
		} catch (ServerException e)
		{
			System.out.println(e.getMessage());
			exchange.sendResponseHeaders(HttpURLConnection.HTTP_INTERNAL_ERROR, -1);
			return;
		}

		exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
		xs.toXML(result, exchange.getResponseBody());
		exchange.getResponseBody().close();
	}

}
