using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.OleDb;
using System.IO;

namespace Data
{
    public class DataConnecter
    {
        protected OleDbDataAdapter DataAdaptor1 = new OleDbDataAdapter();
        public string ErrorMessage = "";

        public DataConnecter(string ConnectionString)
        {
            OleDbConnection Connection1 = new OleDbConnection(ConnectionString);
            this.DataAdaptor1.SelectCommand = new OleDbCommand("", Connection1);
            this.DataAdaptor1.InsertCommand = new OleDbCommand("", Connection1);
        }

        public DataTable DataSelect(string query)
        {
            DataTable dt = new DataTable();

            try
            {
                DataAdaptor1.SelectCommand.CommandText = query;
                DataAdaptor1.SelectCommand.Connection.Open();
                DataAdaptor1.Fill(dt);
                DataAdaptor1.SelectCommand.Connection.Close();
                ErrorMessage = "";
            }
            catch(Exception err)
            {
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
                DataAdaptor1.InsertCommand.CommandText = query;
                DataAdaptor1.InsertCommand.Connection.Open();
                Result = DataAdaptor1.InsertCommand.ExecuteNonQuery();
                DataAdaptor1.InsertCommand.Connection.Close();
                ErrorMessage = "";
                return Result;
            }
            catch (Exception err)
            {
                ErrorMessage = err.Message;
                DataAdaptor1.InsertCommand.Connection.Close();
                return 0;
            }
        }
            public int DataUpdate(string query)
        {
            return DataInsert(query);
        }
        public int DataDelete(string query)
        {
            return DataInsert(query);
        }
    }
}
