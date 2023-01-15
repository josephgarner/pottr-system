import { Context } from "koa";

export const handleError = async (logic: () => Promise<void>, ctx: Context) => {
  try {
    await logic();
  } catch (error) {
    ctx.response.status = 400;
    ctx.response.body = error;
    ctx.app.emit("error", error, ctx);
  }
};
