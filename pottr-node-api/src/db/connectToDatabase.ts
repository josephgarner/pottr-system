import mongoose from "mongoose";

export const connectToDatabase = async () => {
  const uri = process.env.DATABASE_URI || "mock";
  const database = process.env.DATABASE || "database";
  try {
    mongoose.set("strictQuery", false);
    mongoose.connect(`mongodb://${uri}/${database}`, () => {
      console.log("Connected to Database");
    });
    mongoose.connection.on("error", (err) => {
      console.error(err);
    });
  } catch (error) {
    console.error(error);
  }

  if (!mongoose.connection) {
    console.error("failed to establish a connection to the database");
  }
};
