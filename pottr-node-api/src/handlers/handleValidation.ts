import { Context } from "koa";
import { AnyZodObject } from "zod";

export const handleValidation = async (schema: AnyZodObject, ctx: Context) => {
  await schema.parseAsync({
    body: ctx.request.body,
    query: ctx.query,
    params: ctx.params,
  });
};
