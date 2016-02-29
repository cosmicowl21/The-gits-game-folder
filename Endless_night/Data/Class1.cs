using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
using System.IO;

/*
This the class that creates 
*The database connection
*The DataSelect
*The DataInsert
*The DataUpdate
*The DataDelete
*/

namespace Data
{
    public partial class DataConnecter
    {
        /*
        SqlConnection ABC = new SqlConnection("Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename="G:\endlesnight - Copy\proj.win32\Database\Hi.mdf";Integrated Security=True;Connect Timeout=30");
        SqlConnection AC = new SqlConnection("Data Source=(LocalDB)=MSSQLLocalDB;AttachDbFilename="G:\endlesnight - Copy\proj.win32\Database\Hi.mdf";Integrated Security=True;Connect Timeout=30");
        */

        protected SqlDataAdapter DataAdaptor1 = new SqlDataAdapter();
        public string ErrorMessage = "";

        public DataConnecter(string ConnectionString)
        {
            SqlConnection Connection1 = new SqlConnection(ConnectionString);
            this.DataAdaptor1.SelectCommand = new SqlCommand("", Connection1);
            this.DataAdaptor1.InsertCommand = new SqlCommand("", Connection1);
        }

        public DataTable DataSelect(string query)
        {
            //Here is the Dataselect  
            
            DataTable dt = new DataTable();

            try
            {
                /*
                The try will get the query
                It will open a connection
                Fill the dataTable
                Then close the connection
                If there is an error a message will alert the user
                */
                DataAdaptor1.SelectCommand.CommandText = query;
                DataAdaptor1.SelectCommand.Connection.Open();
                DataAdaptor1.Fill(dt);
                DataAdaptor1.SelectCommand.Connection.Close();
                ErrorMessage = "";
            }
            catch(Exception err)
            {
                /*
                The catch will get any error messages
                Then it will close the connection 
                */
                ErrorMessage = err.Message;
                DataAdaptor1.SelectCommand.Connection.Close();
            }

                return dt;
        }
        public int DataInsert(string query)
        {
            int Result = 0;

            try
            {
             /*
             The try will get the query
             It will open a connection
             It shows the effected rows 
             Then close the connection
             If there is an error a message will alert the user
             Result is returned to show what was altered
             */
                DataAdaptor1.InsertCommand.CommandText = query;
                DataAdaptor1.InsertCommand.Connection.Open();
                Result = DataAdaptor1.InsertCommand.ExecuteNonQuery();
                DataAdaptor1.InsertCommand.Connection.Close();
                ErrorMessage = "";
                return Result;
            }
            catch (Exception err)
            {
               /*
               The catch will get any error messages
               Then it will close the connection 
               */
                ErrorMessage = err.Message;
                DataAdaptor1.InsertCommand.Connection.Close();
                return 0;
            }
          }
        public int DataUpdate(string query)
        {
            //DataUpdate returns DataInsert
            return DataInsert(query);
        }
        public int DataDelete(string query)
        {
            //DataDelete returns DataInsert
            return DataInsert(query);
        }
        
    }
}
